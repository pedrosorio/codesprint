#include <iostream>
#include <cmath>
#include <string>
#include <sys/time.h>

using namespace std;

const int maxN = 510, maxM = 110;
const int epochs = 100;
const double alpha = 0.01, lambda = 20;

double getTime(){
   timeval tv; 
   gettimeofday(&tv, 0); 
   return tv.tv_sec + tv.tv_usec * 1e-6;
};

double starttime = getTime();

long double sigmoid(long double *x, long double *theta, int M) {
	long double prod=0;
	for(int i=0;i<M;i++)
		prod+=x[i]*theta[i];
		
	return 1/(1+exp(-prod));
}

void train(int *cl, long double vecs[maxN][maxM], long double *theta, int N ,int M, double alpha, double lambda) {
	for(int i=0;i<M;i++)
		theta[i] = 0;
	while(getTime()-starttime < 2.5) {
		for(int tr=0;tr<N;tr++) {
			for(int th=0;th<M;th++)
				theta[th] = theta[th] + alpha * ((cl[tr] - sigmoid(vecs[tr], theta, M))*vecs[tr][th] - 2*lambda*theta[th]);
		}
	}
}


int main() {
	long double vecs[maxN][maxM], mean[maxM], std[maxM], theta[maxM];
	int N,M,q;
	int cl[maxN];
	cin >> N >> M;
	string s;
	
	//training input
	for(int i=0;i<N;i++) {
		int auxi;
		char auxc;
		cin >> s;
		cin >> cl[i];
		if(cl[i] == -1)
			cl[i]=0;
		for(int j=0;j<M;j++) {
			cin >> auxi >> auxc >> vecs[i][j];
		}
	}
	
	
	
	//normalize by mean and std
	for(int i=0;i<M;i++) {
		mean[i] = 0;
		for(int j=0;j<N;j++)
			mean[i]+=vecs[j][i];
		mean[i]/=N;
	}
	
	
	for(int i=0;i<M;i++) {
		std[i] = 0;
		for(int j=0;j<N;j++)
			std[i]+=(vecs[j][i]-mean[i])*(vecs[j][i]-mean[i]);
		std[i]=sqrt(std[i]/N);
	}
	//cout << "Features " << endl;
	for(int i=0;i<M;i++) {
		for(int j=0;j<N;j++) {
			if(std[i]!=0) 
				vecs[j][i] = (vecs[j][i] - mean[i])/std[i];
		}
	}
	

	train(cl,vecs,theta,N,M,alpha,lambda);
	
	//test data
	cin >> q;
	for(int i=0;i<q;i++) {
		int auxi;
		char auxc;
		cin >> s;
		for(int j=0;j<M;j++) {
			cin >> auxi >> auxc >> vecs[0][j];
			if(std[j]!=0)
				vecs[0][j] = (vecs[0][j] - mean[j])/std[j];
		}
		cout << s;
		if(sigmoid(vecs[0],theta,M) > 0.5)
			cout << " +1" << endl;
		else
			cout << " -1" << endl;
	}
	
	return 0;
}
