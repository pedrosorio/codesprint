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

vector<int> note;

void flow(int v,vector<list<int> > &E, vector<int> &C, int cc) {
  list<int>::iterator it;
  if(C[v]==cc)
    return;
  C[v]=cc;
  for(it=E[v].begin();it!=E[v].end();it++)
    flow(*it,E,C,cc);
}

bool findf(int v,vector<list<int> > &E, vector<int> &C, int f) {
  note.push_back(v);
  C[v]=0;
  list<int>::iterator it;
  for(it=E[v].begin();it!=E[v].end();it++) {
    if(*it == f)
      return true;
    if(C[*it] == 0)
      continue;
    bool ans=findf(*it,E,C,f);
    if(ans)
      return true;
  }
  return false;
}

int main() {
  int N,M,a,b;
  cin >> N >> M;
  vector<list<int> > E(N);
  vector<pair<int,int> > LE;
  vector<int> C(N,0);
  list<int>::iterator it;
  for(int i=0;i<M;i++) {
    cin >> a >> b;
    LE.push_back(make_pair(a,b));
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  int cc=0;
  for(int i=0;i<N;i++) {
    if(C[i]==0)
      flow(i,E,C,++cc);
  }
  
  for(int i=0;i<M;i++) {
    a=LE[i].first; b=LE[i].second;
    E[a].remove(b); E[b].remove(a);
    int c=C[a];
    bool ans=findf(a,E,C,b);
    if(!ans)
      cc++;
    for(int j=0;j<note.size();j++)
      C[note[j]] = c;
    note.clear();
    cout << cc << endl;
  }
  
  return 0;
}
