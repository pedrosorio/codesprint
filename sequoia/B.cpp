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

int main() {
  string s;
  cin >> s;
  int N=s.size();
  vector<int> r;
  r.push_back(0);
  for(int i=0;i<N;i++)
    r.push_back(s[i]-'0');
  r.push_back(0);
  int ct=0;
  if(N==0) {
    cout << 0 << endl;
    return 0;
  }
  if(N==1) {
    if(r[1]>0)
      cout << 1 << endl;
    else
      cout << 0 << endl;
    return 0;
  }
  /*
  if(r[0]>0 && (r[1]<1 || r[1]==3)) {
    ct++;
    r[1]--;
    r[0]=0;
  }
  
  if(r[N-1]>0 && (r[N-2]<1 || r[N-2]==3)) {
    ct++;
    r[N-2]--;
    r[N-1]=0;
  }

  for(int i=1;i<N-1;i++) {
    if(r[i]>0 && (r[i-1]<1 || r[i-1]==3) && (r[i+1]<1 || r[i+1]==3)) {
      ct++;
      r[i-1]--;
      r[i+1]--;
      r[i]=0;
    }
  }
  */
  
  for(int d=1;d<4;) {
 
    for(int i=1;i<=N;i++) {
      if(r[i]>0 && r[i]<=d) {
        ct++;
        r[i-1]--;
        r[i+1]--;
        r[i]=0;
      }
    }
    bool cd=false;   
    for(int i=1;i<N && !cd;i++) {
      if(r[i]==d)
        cd=true;
    }
    if(!cd)
      d++; 
      
  }
  
  cout << ct << endl;
  
  
  return 0;
}
