#include <iostream>

using namespace std;

const int maxN=200010;
const long long int mod = 1000000007LL;

int x[maxN],p[maxN];


int main() {
	int T;
	cin >> T;
	for(int cs=0;cs<T;cs++) {
		int N;
		cin >> N;
		for(int i=0;i<N;i++)
			cin >> x[i];
		for(int i=0;i<N;i++)
			cin >> p[i];
		long long int km=0;
		for(int i=0;i<N;i++) {
			for(int j=i+1;j<N;j++) {
				int pp = (p[i] > p[j])?p[i]:p[j];
				km += pp * (x[j]-x[i]);
				km = km%mod;
			}
		}
		
		cout << km <<endl;
	}
}
