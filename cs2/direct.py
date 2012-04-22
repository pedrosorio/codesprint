T = int(raw_input())

for i in range(T):
	N = int(raw_input())
	x = map(int,raw_input().split())
	pop = map(int,raw_input().split())
	dst = 0
	for j in range(N-1):
		for k in range(j+1,N):
			if pop[k] > pop[j]:
				dst += (x[k]-x[j]) * pop[k]
			else:
				dst += (x[k]-x[j]) * pop[j]
			dst = dst%1000000007
		      
	print dst
