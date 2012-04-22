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
#include <cstring>

using namespace std;

int main() {
  string file;
  getline(cin,file);
  ifstream input(file.c_str(),ios::binary);
  char bufst[1000],bufim[300*300*3],bufout[300*300*3];
  int kernel[3][3] = {{-4,-2,0},{-2,1,2},{0,2,4}};
  int add;
  if(input.is_open()) {
    input.read(bufst,14);
    add=bufst[10]+bufst[11]*0xff + bufst[12]*0xffff + bufst[12]*0xffffff;
    input.read(bufst+14,add-14);
    input.read(bufim,300*300*3);
    int x=(unsigned char)bufim[0],y=(unsigned char)bufim[1];
  }
  memcpy(bufout,bufim,300*300*3);
  input.close();
  for(int r=1;r<299;r++) {
    for(int p=1;p<299;p++) {
      for(int c=0;c<3;c++) {
        int s=0;
        for(int dr=-1;dr<2;dr++) {
          for(int dp=-1;dp<2;dp++) {
            int v = (unsigned char)bufim[3*(300*(r+dr)+p+dp)+c];
            //bottom up RGB image argh! (the kernel should be applied
            //upside-down: kernel[1-dr][dp+1] but the contest had a "bug")
            s+=v*kernel[dr+1][dp+1]; 
          }
        }
        
        bufout[3*(300*r+p)+c] = (char)min(255,max(0,s));
      }
    }
  }
  getline(cin,file);
  ofstream output(file.c_str(),ios::binary);
  if(output.is_open()) {
    output.write(bufst,add);
    output.write(bufout,300*300*3);
  }
  output.close();
  
  
  return 0;
}
