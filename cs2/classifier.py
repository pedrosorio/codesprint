[N,M] = map(int, raw_input().split())
avgp = 0
avgn = 0
cp,cn=0,0
for i in xrange(N):
    line = raw_input().split()
    score = int(line[1])
    avg = 0
    for item in line[2:]:
        fet = item.split(":")
        avg += float(fet[1])
    avg = avg/M
    if score==-1:
        avgn+=avg
        cn+=1
    else:
        avgp+=avg
        cp+=1
avgp/=cp
avgn/=cn
Q=int(raw_input())
for i in xrange(Q):
    line = raw_input().split()
    avg = 0
    for item in line[1:]:
        fet = item.split(":")
        avg += float(fet[1])
    avg = avg/M
    if abs(avgp-avg)>abs(avgn-avg): score = "-"
    else: score = "+"
    print line[0]+" "+score+"1"
