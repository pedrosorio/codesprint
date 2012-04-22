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
#include <fstream>
#include <unordered_map>

using namespace std;

typedef long long LL;

class scheduler {
  private:
    map<LL, set<LL> > time_map; //map timestamp to set of ID's
    unordered_map<LL,LL> id_todo; //hash from ID to corresponding timestamp
    string file;
  public:
    scheduler(string file);
    void Save();
    void Set(LL A, LL T);
    void List(LL T);
    void Del(LL A);
    void Clear();
};

scheduler::scheduler(string filestore) {
  file = filestore;
  ifstream input(file);
  int N,M,T,A;
  if(input.is_open()) {
    input >> N;
    for(int i=0;i<N;i++) {
      input >> T >> M;
      for(int j=0;j<M;j++) {
        input >> A;
        Set(A,T);
      }
    }
  }
  input.close();
};

void scheduler::Save() {
  map<LL, set<LL> >::iterator it;
  set<LL>::iterator sit;
  ofstream output(file);
  if(output.is_open()) {
    output << time_map.size() << endl;
    for(it = time_map.begin();it!=time_map.end();it++) {
      output << it->first << endl;
      output << it->second.size() << endl;
      for(sit = it->second.begin();sit!=it->second.end();sit++)
        output << *sit << ' ';
      output << endl;
    }
  }
  output.close();
};

void scheduler::Set(LL A, LL T) {
  map<LL, set<LL> >::iterator it;
  unordered_map<LL, LL>::iterator itu = id_todo.find(A);
  //if current user has an update scheduled
  if(itu!=id_todo.end()) {
    //if the timestamp is the same, ignore
    if(itu->second == T)
      return;
    //otherwise, remove update
    it = time_map.find(itu->second);
    it->second.erase(A);
  }
  
  //set the timestamp of the inserted user
  id_todo[A] = T;
  it = time_map.find(T);
  //if the required timestamp doesn't exist
  if(it==time_map.end()) {
    //create a new set with the user inside
    set<LL> ins;
    ins.insert(A);
    time_map[T] = ins;
  }
  else {
    //add the user to the existing set
    it->second.insert(A);
  }
};

void scheduler::List(LL T) {
  map<LL, set<LL> >::iterator it;
  set<LL>::iterator sit;
  it = time_map.begin();
  bool space=false;
  while(it!=time_map.end() && it->first <= T) {
    for(sit=it->second.begin();sit!=it->second.end();sit++) {
      if(space)
        cout << ' ';
      else
        space=true;
      cout << *sit;
    }
    it++;
  }
  cout << endl;
};

void scheduler::Del(LL A) {
  map<LL, set<LL> >::iterator it;
  unordered_map<LL, LL>::iterator itu = id_todo.find(A);
  //if user has an update scheduled
  if(itu!=id_todo.end()) {
    //remove update
    it = time_map.find(itu->second);
    it->second.erase(A);
    id_todo.erase(itu);
  }
};

void scheduler::Clear() {
  id_todo.clear();
  time_map.clear();
};
    
int main() {
  scheduler S("pedrosorio_file.txt");
  int N;
  LL A,T;
  cin >> N;
  string order;
  for(int i=0;i<N;i++) {
    cin >> order;
    if(order.compare("set")==0) {
      cin >> A >> T;
      S.Set(A,T);
    }
    else if(order.compare("list")==0) {
      cin >> T;
      S.List(T);
    }
    else if(order.compare("del")==0) {
      cin >> A;
      S.Del(A);
    }
    else if(order.compare("clear")==0)
      S.Clear();
  }
  S.Save();
  
  return 0;
}
