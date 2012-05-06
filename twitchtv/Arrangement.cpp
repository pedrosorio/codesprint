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

int won[1001][1001];
list<int> path;

int main() {
  int T;
  cin >> T;
  char ch;
  for(int c=0;c<T;c++) {
    int N;
    cin >> N;
    for(int i=0;i<N;i++) {
      for(int j=0;j<N;j++) {
        cin >> ch;
        won[i][j]= ch-'0';
      }
    }
    
    path.push_back(0);
    for(int i=1;i<N;i++) {
      list<int>::iterator it=path.begin();
      while(it!=path.end() && won[*it][i])
        it++;
      if(it==path.end())
        path.push_back(i);
      else
        path.insert(it,i);
    }
    
    list<int>::iterator it=path.begin();
    cout << "Yes";
    while(it!=path.end()) {
      cout << " " << *it;
      it++;
    }
    cout << endl;
    path.clear();
    
  }
    
    
  
  return 0;
}
