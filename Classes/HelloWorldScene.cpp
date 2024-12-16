/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

const float tp = 4;
std::stringstream flow;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto str = FileUtils::getInstance()->getStringFromFile("qwq.txt");
	flow << str;
	auto gp = [](float x, float y)->Vec2 {
		return Vec2(y * 200, 1200 - x * 200);
		};
	auto vgo = [](int x)->Vec2 {
		switch (x) {
		case 0:
			return Vec2(1, 0);
		case 1:
			return Vec2(0, 1);
		case 2:
			return Vec2(-1, 0);
		case 3:
			return Vec2(0, -1);
		default:CC_ASSERT(0);
		}
		};
	auto ga = [](float x)->float {
		return 360.0f - x * 90.0f;
		};
	auto ins = [this](auto& x, std::string y) {
		addChild(x.first = Sprite::create(y));
		x.first->setAnchorPoint(Vec2(0, 1));
		x.second.pushBack(DelayTime::create(7+tp));
		};
	for (int i = 0;i < 3;i++) ins(a[i], "a.png");
	for (int i = 3;i < 6;i++) ins(a[i], "b.png");
	ins(a[6], "c.png");
	ins(a[7], "d.png");
	ins(b, "e.png");
	b.first->setAnchorPoint(Vec2(0.5, 0.5));
	int gx, gy, go, lo;
	for (int i = 0;i < 8;i++) {
		flow >> gx >> gy;
		a[i].first->setPosition(gp(gx, gy));
	}
	flow >> gx >> gy >> go;
	b.first->setPosition(gp(gx+0.5, gy+0.5));
	b.first->setRotation(ga(go));
	lo = go;
	for (int turn = 0;turn < 83;turn++) {
		for (int i = 0;i < 8;i++) {
			flow >> gx >> gy;
			a[i].second.pushBack(EaseExponentialInOut::create(MoveTo::create(tp, gp(gx, gy))));
		}
		flow >> gx >> gy >> go;
		Vec2 pos = gp(gx + 0.5, gy + 0.5);
		if (lo == go) {
			b.second.pushBack(EaseExponentialInOut::create(MoveTo::create(tp, pos)));
		}
		else {
			auto move = MoveTo::create(tp, pos);
			auto rota = RotateTo::create(tp, ga(go));
			b.second.pushBack(EaseInOut::create(Spawn::createWithTwoActions(move,rota ),5));
		}
		lo = go;
	}
	////e->runAction(Spawn::createWithTwoActions(moveBy, qwq);

	for (int i = 0;i < 8;i++) {
		a[i].first->runAction(Sequence::create(a[i].second));
	}
	b.first->runAction(Sequence::create(b.second));
	addChild(label = Label::createWithTTF("0", "ARLRDBD.TTF", 72));
	cnt = 0;
	label->setPosition(400, 100);
	schedule([this](float dt) {label->setString(std::to_string(++cnt));}, tp, CC_REPEAT_FOREVER, tp+7.5f, "label");
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
