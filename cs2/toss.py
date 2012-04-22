T = int(raw_input())

for i in range(T):
	lst = raw_input().split()
	n = int(lst[0])
	m = int(lst[1])
	if m==n:
		print "0.00"
	elif m==0:
		print(str((2**(n+1)-2)) + ".00")
	else:
		v=0
		for j in range(n-m):
			v=v+2**(n-j)
		print(str(v) + ".00")
