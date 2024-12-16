#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define rep(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii<=Ii##_;Ii++)
#define per(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii>=Ii##_;Ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned uint;
typedef long double db;
#define fir first
#define sec second
#define siz(Aa) ((int)(Aa).size())
#define all(Aa) (Aa).begin(),(Aa).end()
#define ckmx(Aa,Bb) (Aa=max(Aa,Bb))
#define ckmn(Aa,Bb) (Aa=min(Aa,Bb))
mt19937_64 rgen(time(0)+size_t(new(char)));
// orientations
const int dx[]={0,-1,0,1};
const int dy[]={1,0,-1,0};
ull w[20];
const ull base=1011451423;
struct pos{
	int x,y;
	friend ostream&operator<<(ostream&os,const pos&v){
		os<<v.x<<" "<<v.y<<"  ";
		return os;
	}
	ull hsh()const{
		return w[x*4+y];
	}
	pos operator+(int o)const{
		return {x+dx[o],y+dy[o]};
	}
	pos&operator+=(int o){
		x+=dx[o];
		y+=dy[o];
		return*this;
	}
};
struct node{
	pos a[3];// 1x1
	pos b[3];// 2x1 (vertical)
	pos c;// 1x2
	pos d;// 2x2
	pos e;// sofa (anchor at middle block)
	int o;// sofa ori
	ull hsh()const{
		ull res=0;
		rep(i,0,2) res+=a[i].hsh();
		res*=base;
		rep(i,0,2) res+=b[i].hsh();
		res*=base;
		res+=c.hsh();
		res*=base;
		res+=d.hsh();
		res*=base;
		res+=e.hsh();
		res*=base;
		res+=o;
		return res;
	}
};
const node ini={
	{{4,1},{4,2},{4,3}}// a
	,{{0,0},{0,3},{2,3}}// b
	,{2,1}// c
	,{0,1}// d
	,{3,0}// e
	,0// o
};
queue<pair<node,int>> q;
unordered_map<ull,node> s;
unordered_map<ull,ll> ss;
void ins(const node&x,int cnt,const node&lst){
	ull xh=x.hsh();
	if(!s.count(xh)){
		q.emplace(x,cnt);
		s[xh]=lst;
	}
	ss[xh]+=ss[lst.hsh()];
}
bool mp[5][4];
void ins(pos x){
	assert(!mp[x.x][x.y]);
	mp[x.x][x.y]=true;
}
void del(pos x){
	assert(mp[x.x][x.y]);
	mp[x.x][x.y]=false;
}
void get(const node&x){
	rep(i,0,4) rep(j,0,3) mp[i][j]=true;
	rep(i,0,2){
		del(x.a[i]);
		del(x.b[i]);
		del(x.b[i]+3);
	}
	del(x.c);
	del(x.c+0);
	del(x.d);
	del(x.d+0);
	del(x.d+3);
	del((x.d+3)+0);
	del(x.e);
	for(int oo:{-1,1}){
		int o=(x.o+oo)&3;
		del(x.e+o);
	}
	int cnt=0;
	rep(i,0,4) rep(j,0,3) cnt+=mp[i][j];
	assert(cnt==2);
}
bool chk(pos x){
	return x.x>=0 && x.x<5 && x.y>=0 && x.y<4 && mp[x.x][x.y];
}
ofstream os("qwqraw.txt");
void print(const node&x){
// 	static char pr[5][4];
// 	rep(i,0,4) rep(j,0,3) pr[i][j]='.';
// #define fun(t) pr[(t).x][(t).y]
// 	rep(i,0,2){
// 		fun(x.a[i])='a';
// 		fun(x.b[i])='b';
// 		fun(x.b[i]+3)='b';
// 	}
// 	fun(x.c)='c';
// 	fun(x.c+0)='c';
// 	fun(x.d)='d';
// 	fun(x.d+0)='d';
// 	fun(x.d+3)='d';
// 	fun((x.d+3)+0)='d';
// 	cout<<"e:"<<x.e.x<<" "<<x.e.y<<" o:"<<x.o<<"\n";
// 	rep(i,0,4){
// 		rep(j,0,3) cout<<pr[i][j];
// 		cout<<"\n";
// 	}
// 	cout.flush();
	os.flush();
	rep(i,0,2) os<<x.a[i];
	rep(i,0,2) os<<x.b[i];
	os<<x.c<<x.d<<x.e<<x.o;
	os<<"\n";
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	rep(i,0,19) w[i]=rgen();
	q.emplace(ini,0);
	s[ini.hsh()]=node();
	ss[ini.hsh()]=1;
	ll total=0;
	while(true){
		assert(!q.empty());
		auto[x,cnt]=q.front();
		q.pop();
		if(x.d.x==3 && x.d.y==1){
			if(cnt>83){
				cout<<total<<endl;
				return 0;
			}
			cout<<"qwq\n";
			total+=ss[x.hsh()];
			continue;
			// while(true){
				// print(x);
				// if(x.hsh()==ini.hsh()) break;
				// x=s[x.hsh()];
			// }
			// return 0;
		}
		get(x);
		rep(i,0,2){
			rep(j,0,3){
				node y=x;
				rep(k,0,1){
					y.a[i]+=j;
					if(!(chk(y.a[i]))) break;
					ins(y,cnt+1,x);
				}
			}
		}
		rep(i,0,2){
			ins(x.b[i]);
			ins(x.b[i]+3);
			rep(j,0,3){
				node y=x;
				rep(k,0,1){
					y.b[i]+=j;
					if(!(chk(y.b[i])&&chk(y.b[i]+3))) break;
					ins(y,cnt+1,x);
				}
			}
			del(x.b[i]);
			del(x.b[i]+3);
		}
		{
			ins(x.c);
			ins(x.c+0);
			rep(j,0,3){
				node y=x;
				rep(k,0,1){
					y.c+=j;
					if(!(chk(y.c)&&chk(y.c+0))) break;
					ins(y,cnt+1,x);
				}
			}
			del(x.c);
			del(x.c+0);
		}
		{
			ins(x.d);
			ins(x.d+0);
			ins(x.d+3);
			ins((x.d+3)+0);
			rep(j,0,3){
				node y=x;
				y.d+=j;
				if(chk(y.d)&&chk(y.d+0)&&chk(y.d+3)&&chk((y.d+3)+0)){
					ins(y,cnt+1,x);
				}
			}
			del(x.d);
			del(x.d+0);
			del(x.d+3);
			del((x.d+3)+0);
		}
		int op=(x.o+1)&3,oq=(x.o-1)&3;
		if(chk((x.e+x.o)+op)&&chk(((x.e+x.o)+x.o)+op)){
			node y=x;
			y.e=(x.e+x.o)+op;
			y.o=oq;
			ins(y,cnt+1,x);
		}
		if(chk((x.e+x.o)+oq)&&chk(((x.e+x.o)+x.o)+oq)){
			node y=x;
			y.e=(x.e+x.o)+oq;
			y.o=op;
			ins(y,cnt+1,x);
		}
		{
			node y=x;
			y.e=x.e+op;
			rep(k,0,1){
				if(!chk(y.e+op)) break;
				ins(y,cnt+1,x);
				y.e+=op;
			}
		}
		{
			node y=x;
			y.e=x.e+oq;
			rep(k,0,1){
				if(!chk(y.e+oq)) break;
				ins(y,cnt+1,x);
				y.e+=oq;
			}
		}
	}
return 0;}
/*
*/