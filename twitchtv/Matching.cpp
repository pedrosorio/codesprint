#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const long long MOD = 1000000007;


long long exp(long long a, long long m) {
  if(m==1)
    return a;
  if(m==2)
    return (a*a)%MOD;
  long long r;
  r = exp(a,m/2);
  r = (r*r)%MOD;
  if(m%2)
    r = (r*a)%MOD;
  
  return r;
}


int main() {
  int N;
  cin >> N;
  long long v=1,dv=1;
  for(int i=N+2;i<=2*N;i++)
    v=(v*i)%MOD;
  for(int i=1;i<=N;i++)
    dv=(dv*i)%MOD;
  
  dv = exp(dv,MOD-2);
  
  v = (v * dv)%MOD;
  
  /*
  for(int i=0;i<=100;i++)
    ways[i][0] = 1;
  for(N=1;N<=100;N++) {
    for(int m=1;m<=N;m++) {
      ways[m][m] = ways[m][m-1];
      for(int b=m+1;b<=N;b++)
        ways[b][m] = (ways[b-1][m] + ways[b][m-1])%MOD;
    }
    cout << N << ": " << ways[N][N] << endl;
  }
  */
  
  cout << v << endl;
  
  return 0;
}
