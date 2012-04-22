#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
using namespace std;

const int maxt=10010;
const long double eps=1e-6;

//structure that contains the id, coords, and (id of) questions related to a topic
struct topic {
	int id;
	long double x,y;
	vector<int> questions;
} topics[maxt];


bool sortfun1(const struct topic& i, const struct topic& j) {
	return i.id < j.id;
}

bool sortfun2(int i, int j) {
	return j<i;
}

bool sortfun3(const pair<long double,int> &i, const pair<long double,int> &j) {
	if(abs(i.first - j.first) < eps)
		return j.second < i.second;
	return i.first < j.first;
}


int main() {
	int T,Q,N,realQ=0;
	//map from topic ID's to topic index in the array (for question insertion)
	unordered_map<int,int> id2index;
	cin >> T >> Q >> N;
	//read topic ID's and coordinates
	for(int i=0;i<T;i++) {
		cin >> topics[i].id >> topics[i].x >> topics[i].y;
		id2index[topics[i].id] = i;
	}
	int Qid,Qn,top;
	//read question ID's
	for(int i=0;i<Q;i++) {
		cin >> Qid >> Qn;
		if(Qn)
			realQ++;
		//and topics they are associated with
		for(int j=0;j<Qn;j++) {
			cin >> top;
			topics[id2index[top]].questions.push_back(Qid);
		}
	}
	
	//sort topics in ascending ID order
	sort(topics,topics+T,sortfun1);
	
	//sort the questions associated with each topic in descending ID order
	for(int i=0;i<T;i++)
		sort(topics[i].questions.begin(),topics[i].questions.end(),sortfun2);
	
	char c;
	int n;
	long double x,y;
	pair<long double,int> distances[maxt]; 
	//process queries
	for(int i=0;i<N;i++) {
		cin >> c >> n >> x >> y;
		//find (squared)distances from this location to all topics
		for(int j=0;j<T;j++)
			distances[j] = pair<long double,int>((x-topics[j].x)*(x-topics[j].x)+(y-topics[j].y)*(y-topics[j].y), j);
		//and sort topics in ascending order of distance (primary) and descending ID (secondary)
		sort(distances,distances+T,sortfun3);
		
		
		


		int ct=0,t=0;
		
		if(c=='t') {
			while(ct<n && t<T) {
				if(ct!=0)
					cout << ' ';
				cout << topics[distances[t].second].id;
				t++;
				ct++;
			}
			cout << endl;
		}
		else {
			//hash that contains questions reported (topics never repeat)
			unordered_set<int> reported;
			pair<long double, int> dists[realQ];
			while(ct < realQ && t<T) {
				int q=0;
				while(ct < realQ && q < topics[distances[t].second].questions.size()) {
					//if the question has already been reported, go to the next
					if(reported.count(topics[distances[t].second].questions[q])) {
						q++;
						continue;
					}
					reported.insert(topics[distances[t].second].questions[q]);
					dists[ct] = pair<long double, int>(distances[t].first, topics[distances[t].second].questions[q]);
					q++;
					ct++;
				}
				t++;
			}
			reported.clear();
			sort(dists,dists+realQ,sortfun3);
			int j;
			for(j=0;j<n-1 && j<realQ-1;j++)
				cout << dists[j].second << ' ';
			cout << dists[j].second << endl;
		}
	}
	return 0;
}
		
