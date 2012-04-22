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

void print_vec(vector<int> &v) {
  for(int i=0;i<v.size();i++)
    cout << v[i] << ' ';
}

int main() {
  int N;
  cin >> N;
  vector<int> seq(N);
  int cmp,L=1;
  
  for(int i=0;i<N;i++)
    cin >> seq[i];
  cmp=seq[0];
  for(int i=1;i<N;i++) {
    if(L%2) {
      if(seq[i]>cmp) {
        cmp = seq[i];
        L++;
      }
      else
        cmp = seq[i];
    }
    else {
      if(seq[i]<cmp) {
        cmp = seq[i];
        L++;
      }
      else
        cmp = seq[i];
    }
  }
  
  cout << L << endl;
  
    
  return 0;
}
