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

int con[101];
vector<int> edges[101];

void fill(int i,int c) {
  if(con[i]!=-1)
    return;
  con[i]=c;
  for(int j=0;j<edges[i].size();j++)
    fill(edges[i][j],c);
}

int main() {
  int K;
  char ch;
  cin >> K;
  vector<int> w(K);
  for(int i=0;i<K;i++)
    cin >> w[i];
  
  //Model the problem as a graph that has edges where permutations are possible
  for(int i=0;i<K;i++) {
    con[i]=-1;
    for(int j=0;j<K;j++) {
      cin >> ch;
      if(ch=='Y')
        edges[i].push_back(j);
    }
  }
  
  //Find connected components
  int c=0;
  for(int i=0;i<K;i++) {
    if(con[i]==-1) {
      c++;
      fill(i,c);
    }
  }
  
  //Since swapping allows to place the parts that belong to a connected component
  //in any order, let's sort them to maximize the center of mass
  vector<int> swap[c],pos[c];
  for(int i=0;i<K;i++) {
    swap[con[i]-1].push_back(w[i]);
    pos[con[i]-1].push_back(i);
  }
  
  for(int i=0;i<c;i++)
    sort(swap[i].begin(),swap[i].end());
  
  for(int i=0;i<c;i++) {
    for(int j=0;j<pos[i].size();j++)
      w[pos[i][j]] = swap[i][j];
  }
  
  cout << w[0];
  for(int i=1;i<K;i++)
    cout << ' ' << w[i];
  cout << endl;
  
  
  
  return 0;
}
