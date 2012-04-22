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
  int T,N;
  cin >> T;
  for(int c=0;c<T;c++) {
    cin >> N;
    if(N%4 == 2 || N%4 == 3)
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
  }
  
  return 0;
}
