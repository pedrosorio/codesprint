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

bool check(vector<int> &board, int move, int player) {
  int row=3*(move/3),col=move%3;
  if(board[row]==board[row+1] && board[row]==board[row+2])
    return true;

  if(board[col]==board[col+3] && board[col]==board[col+6])
    return true;
  
  
  if(move==0 || move==4 || move==8) {
    if(board[0]==board[4] && board[0]==board[8])
      return true;
  }
  
  if(move==2 || move==4 || move==6) {
    if(board[2]==board[4] && board[2]==board[6])
      return true;
  }
  
  return false;
}

pair<int,int> play(vector<int> &board, int plays, int player) {
  vector<int> b = board;
  pair<int,int> p;
  int best=player,bestm;
  for(int i=0;i<9;i++) {
    if(b[i]==0) {
      if(best==player)
        bestm=i;
      b[i]=player;
      if(!check(b,i,player)) {
        if(plays==8) {
          if(best!=-player) {
            best=0;
            bestm=i;
          }
        }
        else {
          p = play(b,plays+1,-player);
          if(abs(p.second - player) > abs(best - player)) {
            best = p.second;
            bestm = i;
          }
        }
      }
      b[i]=0;
    }
  }
  
  p.first = bestm;
  p.second = best;
  
  return p;
}
            
  
  

int main() {
  int n;
  vector<int> board(9);
  pair<int,int> p;
  cin >> n;
  for(int i=0;i<n;i++) {
    for(int i=0;i<9;i++) 
      cin >> board[i];
    int plays=0;
    for(int i=0;i<9;i++) {
      if(board[i]!=0)
        plays++;
    }
    p = play(board,plays,1);
    cout << p.first << endl;
  }
  
  
  return 0;
}
