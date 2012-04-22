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

vector<bool> sieve;

int sumdigi(int n) {
  int s=0;
  while(n>0) {
    s+=n%10;
    n/=10;
  }
  return s;
}

int main() {
  int n;
  cin >> n;
  vector<bool> sieve(50*n+1,false);
  sieve[1]=false;
  int ct=0;
  for(int i=2;;i++) {
    if(sieve[i])
      continue;
    if(!sieve[sumdigi(i)]) {
      ct++;
      if(ct==n) {
        cout << i << endl;
        return 0;
      }
    }
    for(int j=2*i;j<50*n;j+=i)
      sieve[j]=true;
  } 
  
  return 0;
}
