#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 50050

using namespace std;

int v[MAX],ct[MAX];

int main() {
	int T;
	cin >> T;
	for(int cs=0;cs<T;cs++) {
		int N;
		cin >> N;
		for(int i=0;i<N;i++) {
			int ci;
			cin >> ci;
			v[i]=ci;
		}
		sort(v,v+N);

		if(v[N-1]==N) {
			cout << 0 << endl;
			continue;
		}
		ct[0]=0; 
		int cur=0;
		for(int i=0;i<N;i++) {
			if(v[i]!=cur) {
				while(cur < v[i]) {
					cur++;
					ct[cur]=ct[cur-1];
				}
			}
			ct[cur]++;
		}
		while(cur < N-1) {
			cur++;
			ct[cur] = ct[cur-1];
		}
		
		long long int ret=1;
		for(int i=0;i<N;i++) 
			ret = (ret * (ct[i] - i))%1000000007LL;
		
			
		cout << ret << endl;
	}
	
	return 0;
}
