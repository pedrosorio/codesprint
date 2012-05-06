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
#include <cstring>

using namespace std;

int N,M,mp[201][201],visited[201],row[201],col[201];
vector<pair<int, int> > v;
vector<int> lst[201];


//find maximum matching on the graph using DFS
bool find_match(int where) {
     if (where == -1)
       return true;
     for (int i = 0; i < lst[where].size(); i++) {
       int match = lst[where][i];
       if (visited[match] == false) {
         visited[match] = true;
         if (find_match(col[match])) {
           col[match] = where;
           return true;
         }
       }
     }
     return false;
   }

   int how_many(int rows, int cols) { 
      int ret = 0;
      memset(row, -1, sizeof(row));
      memset(col, -1, sizeof(col));
      for (int i = 0; i < rows; i++) {
        memset(visited, 0, sizeof(visited));
        ret += find_match(i);
      }
      return ret;
   }  

int main() {
  cin >> N >> M;
  for(int i=0;i<N;i++) {
    for(int j=0;j<M;j++) {
      cin >> mp[i][j];
      if(mp[i][j])
        lst[i].push_back(j);
    }
  }
  

  cout << how_many(N,M) << endl;
  
  
  
  
  return 0;
}
