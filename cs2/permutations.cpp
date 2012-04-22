#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <sys/time.h>


using namespace std;

double starttime;
int N,V[50][50];
int popsize=200;
int die=150;

double getTime(){
   timeval tv; 
   gettimeofday(&tv, 0); 
   return tv.tv_sec + tv.tv_usec * 1e-6;
};

double getseed(){
	timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec + tv.tv_usec;
}

//Genetic algorithms for the win!!!
class gene {
		vector<int> perm;
		int score;
		void compute_score();
		void rand_perm();
	public:
		gene();
		~gene();
		void mutation();
		void die();
    void set_perm(vector<int> &, int );
		vector<int> get_perm();
		int get_score();
		bool operator<(const gene&) const;
};

void gene::compute_score() {
	score=0;
	for(int i=0;i<N-1;i++)
		score += V[perm[i]][perm[i+1]];
}	

void gene::rand_perm() {
	int ch[N];
	perm.resize(N);
	for(int i=0;i<N;i++)
		ch[i]=1;
	for(int i=0;i<N;i++) {
		int rnd = rand()%(N-i);
		int ct=0;
		for(int j=0;;j++) {
			ct+=ch[j];
			if(ct-1 == rnd) {
				perm[i]=j;
				ch[j]=0;
				break;
			}
		}
	}
}

gene::gene() {
	rand_perm();
	compute_score();
}
	

gene::~gene() {
	perm.clear();
}

void gene::mutation() {
	int rnd1 = rand()%N, rnd2 = rand()%N;
	int aux=perm[rnd1];
	perm[rnd1]=perm[rnd2];
	perm[rnd2]=aux;
	compute_score();	
}

void gene::die() {
	rand_perm();
	compute_score();
}

void gene::set_perm(vector<int>& p, int sc) {
  perm = p;
  score = sc;
}
	

vector<int> gene::get_perm() {
	return perm;
}

int gene::get_score() {
	return score;
}

bool gene::operator<(const gene& g2) const {
	return score < g2.score;
}

void print(const vector<int> &v) {
	for(int i=0;i<v.size();i++)
		cout << v[i] << ' ';
	cout << endl;
}

int main(int argc, char *argv[]) {
		starttime=getTime();
    
    //for local optimization purposes
    if(argc == 3) { 
      popsize = atoi(argv[1]);
      die = atoi(argv[2]);
    }
		
		cin >> N;
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++)
				cin >> V[i][j];
		}
		
    //generate a random population
		srand((int)(getseed()));
		gene population[popsize];
    //and sort it by score
		sort(population,population+popsize);
		int scorebest = population[popsize-1].get_score();
		vector<int> pbest = population[popsize-1].get_perm();
		int ct=0;
		while(1) {
			if(++ct%100 == 0) {
				if(getTime() - starttime > 2.8)
					break;
			}
      //kill the worst die permutations from the population and generate random ones
			for(int i=0;i<die;i++)
				population[i].die();
      //on each iteration place the best permutation on the population again
      population[die-1].set_perm(pbest,scorebest);
      //perform a single mutation(switch indices) for the best permutations
			for(int i=die+1;i<popsize;i++)
				population[i].mutation();
      //sort them again by score and find the best -> rinse and repeat
			sort(population,population+popsize);
			if(population[popsize-1].get_score() > scorebest) {
				scorebest = population[popsize-1].get_score();
				pbest = population[popsize-1].get_perm();
			}
			
		}
		
		print(pbest);
		//cout << scorebest << endl;
		return 0;
}
		
