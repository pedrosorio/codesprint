#include <iostream>
#include <map>

using namespace std;

const int maxN = 150010;

int a[maxN];
long long int w[maxN];
map<int,long long int> mp;
map<int,long long int>::iterator it,itaux;

int main() {
	int C;
	cin >> C;
	for(int cs=0;cs<C;cs++) {
		int N;
		cin >> N;
		for(int i=0;i<N;i++)
			cin >> a[i];
		for(int i=0;i<N;i++)
			cin >> w[i];
		
		long long int maxw=w[0];
		mp[a[0]] = w[0];
		for(int i=1;i<N;i++) {
			//find subsequence ending at the smallest number larger than or equal to a[i]
			it=mp.lower_bound(a[i]);
			//if a[i] is smaller or equal to all the previous ones
			if(it==mp.begin()) {
				//if a[i] is equal to a previous one
				if(it->first == a[i]) {
					//and its weight is bigger
					if(it->second < w[i])
						//replace the weight
						it->second = w[i];
				}
				//if a[i] is smaller than all previous ones
				else
					//insert its weight
					it = mp.insert(it, pair<int, long long int>(a[i],w[i]));
				//if this weight is the biggest
				if(it->second > maxw)
					//update the biggest weight so far
					maxw = it->second;
									
				itaux = it;
				//find all the subsequences ending at larger values
				//that have smaller or equal total weight to a[i]
				while(itaux!=mp.end() && itaux->second <= it->second)
					itaux++;
				//and erase them
				mp.erase(++it,itaux);
			}
			//if there are some smaller values than a[i]
			else {
				itaux=it; itaux--;
				//if a[i] is equal to the end of some other subsequence
				if(it!=mp.end() && it->first == a[i]) {
					//if w[i] plus the weight of the heaviest subsequence ending at a smaller value than a[i] is bigger than the current weight
					if(itaux->second + w[i] > it->second)
						//update the total weight of the heaviest subsequence ending at a[i]
						it->second = itaux->second + w[i];
				}
				//if there's no other heaviest subsequence ending at a[i]
				else
					//insert w[i] plus the weight of the heaviest subsequence ending at a value smaller than a[i]
					it = mp.insert(itaux, pair<int,long long int>(a[i],itaux->second+w[i]));
				//if the total weight is the biggest so far
				if(it->second > maxw)
					//update it
					maxw = it->second;
				itaux=it;
				while(itaux!=mp.end() && itaux->second <= it->second)
					itaux++;
				mp.erase(++it,itaux);
			}
		}
		
		cout << maxw << endl;
		mp.clear();
	}
}
				

