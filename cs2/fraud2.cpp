#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <algorithm>

using namespace std;

vector<long long int> fraudreg;

void string_lower(string &s) {
	int sz=s.size();
	for(int i=0;i<sz;i++)
		s[i] = tolower(s[i]);
}

void process_email(string &em) {
	int sz=em.size();
	string temp;
	bool at=false; //change the rules after we've seen @
	for(int i=0;i<sz;i++) {
		if(em[i]!='.' && em[i]!='+') {
			temp.push_back(tolower(em[i]));
			if(em[i]=='@')
				at=true;
		}
		else {
			if(em[i]=='.') {
				if(at)
					temp.push_back('.');	
				continue;
			}
			while(em[++i]!='@');
			at=true;
			temp.push_back('@');
		}
	}
	em = temp;
}

void process_addr(string &ad) {
	string_lower(ad);
	size_t place = ad.find("road");
	if(place != string::npos)
		ad.replace(int(place),4,"rd.");
	place = ad.find("street");
	if(place != string::npos)
		ad.replace(int(place),6,"st.");
}

void process_city(string &ci) {
	string_lower(ci);
}

void process_state(string &st) {
	switch(st[0]) {
		case 'c':
		case 'C': st = "CA"; break;
		case 'i':
		case 'I': st = "IL"; break;
		case 'n':
		case 'N': st = "NY";
	}
}

void process_zip(string &zi) {
	string_lower(zi);
}

unordered_map<string,pair<string, long long int> > ordermap;
unordered_set<long long int> frauds;

int main() {
	int N;
	char c,ordaux[10000];
	cin >> N;
	
	long long int id;
	
	for(int i=0;i<N;i++) {
		string did,em,ad,ci,st,zi,ca;
		cin >> id  >> c;
		cin.getline(ordaux,10000,',');
		did = ordaux;
		cin.getline(ordaux,10000,',');
		em = ordaux;
		process_email(em);
		cin.getline(ordaux,10000,',');
		ad = ordaux;
		process_addr(ad);
		cin.getline(ordaux,10000,',');
		ci = ordaux;
		process_city(ci);
		cin.getline(ordaux,10000,',');
		st = ordaux;
		process_state(st);
		cin.getline(ordaux,10000,',');
		zi = ordaux;
		process_zip(zi);
		cin.getline(ordaux,10000);
		ca = ordaux;
		//cout << id << ',' << did << ',' << em << ',' << ad << ',' << ci << ',' << st << ',' << zi << ',' << ca << endl;
		unordered_map<string,pair<string,long long int> >::iterator it = ordermap.find(did+em);
		unordered_set<long long int>::iterator its;
		if(it==ordermap.end())
			ordermap[did+em] = pair<string,long long int>(ca,id);
		else if(it->second.first != ca) {
			its = frauds.find(it->second.second);
			if(its == frauds.end()) {
				frauds.insert(it->second.second);
				fraudreg.push_back(it->second.second);
			}
			frauds.insert(id);
			fraudreg.push_back(id);
			continue;
		}
		it = ordermap.find(did+ad+ci+st+zi);
		if(it==ordermap.end())
			ordermap[did+ad+ci+st+zi] = pair<string,long long int>(ca,id);
		else if(it->second.first != ca) {
			its = frauds.find(it->second.second);
			if(its == frauds.end()) {
				frauds.insert(it->second.second);
				fraudreg.push_back(it->second.second);
			}
			frauds.insert(id);
			fraudreg.push_back(id);
		}		
	}
	
	sort(fraudreg.begin(),fraudreg.end());
	
	for(int i=0;i<fraudreg.size()-1;i++)
		cout << fraudreg[i] << ',';
	
	cout << fraudreg[fraudreg.size()-1] << endl;
	
	return 0;
}
		
	
