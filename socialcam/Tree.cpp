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

void stars(int nstars,int center,char c) {
   string s2(nstars,c);
   string s(center-nstars/2-1,' ');
   cout << s << s2 << endl;
}


int main() {
  int n;
  cin >> n;
  int mx=7;
  for(int i=2;i<=n;i++) {
    if(i%2)
      mx-=4;
    else
      mx-=2;
    mx+=2*(i+2);
  }
  int center = (mx+1)/2;
  int st=1;
  for(int i=1;i<=n;i++) {
    for(int j=0;j<i+3;j++) {
      stars(st+2*j,center,'*');
    }
    if(i%2)
      st+=2*(i+1);
    else
      st+=2*i;
  }
  for(int i=1;i<=n;i++)
    stars(2*(n/2)+1,center,'|');
  
  
  return 0;
}
