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

vector<pair<int,int> > edges[101];

int maxm[101],s[101];

int main() {
  int N,M,K,u,v,c;
  cin >> N >> M >> K;
  for(int i=0;i<M;i++) {
    cin >> u >> v >> c;
    edges[u-1].push_back(make_pair(v-1,c));
    edges[v-1].push_back(make_pair(u-1,c));
  }
  for(int i=0;i<N;i++) {
    cin >> s[i];
    maxm[i]=0;
  }
  maxm[0]=K;
  
  for(int c=0;c<10000;c++) {
    for(int i=0;i<N;i++) {
      for(int j=0;j<edges[i].size();j++) {
        int v=maxm[edges[i][j].first] - edges[i][j].second;
        if(v>=0)
          maxm[i] = max(maxm[i],(v+s[i])/2);
      }
    }
  }
  
  cout << maxm[N-1] << endl;
  
  
  
  
  return 0;
}
