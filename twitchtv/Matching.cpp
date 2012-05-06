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

//auxiliary function that computes recursively a^m in O(log m)
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
  //The solution corresponds to the N-th Catalan Number
  //Which is equal to (2N!)/(N! * (N+1)!)
  long long v=1,dv=1;
  //Compute numerator
  for(int i=N+2;i<=2*N;i++)
    v=(v*i)%MOD;
  //Compute denominator
  for(int i=1;i<=N;i++)
    dv=(dv*i)%MOD;
  
  //Find modular multiplicative inverse (MMI( of the denominator
  dv = exp(dv,MOD-2);
  
  //Multiply the numerator by the MMI of the denominator (equivalent to dividing and finding the result modulo something)
  v = (v * dv)%MOD;
  
  cout << v << endl;
  
  return 0;
}
