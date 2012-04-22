#include <cstdlib>
#include <sys/time.h>
#include <iostream>

using namespace std;

double getseed(){
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + tv.tv_usec;
}


int main(int argc, char *argv[]) {
  int N;
  if(argc == 2)
    N = atoi(argv[1]);
  else
    N = 50;
  
  cout << N << endl;
    
  srand((int)(getseed()));
  
  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++)
      cout << rand()%100 - 50 << ' ';
    cout << endl;
  }
  
  return 0;
}
