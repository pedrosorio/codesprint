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
    
    /*
    Simple but elusive: 
    Let's assume we have found a path for the first k-1 nodes. Let j be the largest
    such that for all i <= j there is an edge from the i-th node in the path
    to node k. If j == k-1 we can just add node k at the end. If there's no
    node in the path with an arc to node k, then k must have an arc to all nodes in the path.
    In particular, it must have an arc to the first node in the path, thus we can
    add it at the beginning. Otherwise, by definition of j, the (j+1)-th node doesn't
    have an arc to node k, and since the graph is a tournament, k must have an arc
    to the (j+1)-th node, thus we can add it between the j-th and the (j+1)-th node.
    */
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
