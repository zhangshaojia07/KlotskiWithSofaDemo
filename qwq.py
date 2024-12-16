with open("qwq.txt",'r') as f:
    g=f.readlines()[::-1]
    with open("qwq2.txt",'w') as h:
        for i in g:
            h.write(i)