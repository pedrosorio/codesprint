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
  
  /*
  Exact same strategy as for Problem B in round 1B of Google Code Jam
  which ended 30 minutes before the start of this codesprint with the
  bonus that in this one the conditions for travelling are much less tricky
  P.S.: Looking at my times, should have clearly eaten something between the two contests
  
  
  Strategy: keep track of the maximum amount of money found so far that the
  wizard has after arriving at each city. For each city, consider all the 
  cities that have roads connecting to it and if the maximum money found 
  for each of these cities is enough to cross the road, update the maximum
  money in the current city taking into account the cost and the "magical formula"
  Repeat this enough times to make sure the system reaches a steady state
  */
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
