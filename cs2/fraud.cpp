#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>

using namespace std;

vector<int> fraudreg;

class order {
	vector<long long int> orderid;
	vector<string> email;
	vector<string> addr;
	vector<string> city;
	vector<string> state;
	vector<string> zip;
	vector<string> card;
	vector<bool> fraud;
	void string_lower(string &);
	void process_email(string &em);
	void process_addr(string &ad);
	void process_city(string &ci);
	void process_state(string &st);
	void process_zip(string &zi);
	void process_card(string &ca);
	void process_fraud();
	public:
		order();
		order(long long int, string, string, string, string, string, string);
		void add(long long int &, string&, string&, string&, string&, string&, string&);
};

void order::string_lower(string &s) {
	int sz=s.size();
	for(int i=0;i<sz;i++)
		s[i] = tolower(s[i]);
}

void order::process_email(string &em) {
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
	email.push_back(em);
}

void order::process_addr(string &ad) {
	string_lower(ad);
	size_t place = ad.find("road");
	if(place != string::npos)
		ad.replace(int(place),4,"rd.");
	place = ad.find("street");
	if(place != string::npos)
		ad.replace(int(place),6,"st.");
	addr.push_back(ad);
}

void order::process_city(string &ci) {
	string_lower(ci);
	city.push_back(ci);
}

void order::process_state(string &st) {
	switch(st[0]) {
		case 'c':
		case 'C': st = "CA"; break;
		case 'i':
		case 'I': st = "IL"; break;
		case 'n':
		case 'N': st = "NY";
	}
	state.push_back(st);
}

void order::process_zip(string &zi) {
	string_lower(zi);
	zip.push_back(zi);
}

void order::process_card(string &ca) {
	string_lower(ca);
	card.push_back(ca);
}

void order::process_fraud() {
	int sz=fraud.size();
	bool tfraud=false;
	for(int i=0;i<sz;i++) {
		if(card[sz] == card[i])
			continue;
		if((email[sz] == email[i]) || (addr[i]==addr[sz] && city[i]==city[sz] && state[i]==state[sz] && zip[i]==zip[sz])) {
			if(!fraud[i]) {
				fraud[i]=true;
				fraudreg.push_back(orderid[i]);
			}
			if(!tfraud) {
				fraud.push_back(true);
				fraudreg.push_back(orderid[sz]);
			}
			continue;
		}
	}
	if(!tfraud)
		fraud.push_back(false);
}
			
void order::add(long long int &id, string &em, string &ad, string &ci, string &st, string &zi, string &ca) {
	orderid.push_back(id);
	process_email(em);
	process_addr(ad);
	process_city(ci);
	process_state(st);
	process_zip(zi);
	process_card(ca);
	process_fraud();
}	
		
order::order() {

}
	
order::order(long long int id, string em, string ad, string ci, string st, string zi, string ca) {
	add(id,em,ad,ci,st,zi,ca);
}

map<long long int,order> ordermap;

int main() {
	int N;
	char c,ordaux[10000];
	cin >> N;
	long long int id,did;
	
	for(int i=0;i<N;i++) {
		string em,ad,ci,st,zi,ca;
		cin >> id >> c >> did >> c;
		cin.getline(ordaux,10000,',');
		em = ordaux;
		cin.getline(ordaux,10000,',');
		ad = ordaux;
		cin.getline(ordaux,10000,',');
		ci = ordaux;
		cin.getline(ordaux,10000,',');
		st = ordaux;
		cin.getline(ordaux,10000,',');
		zi = ordaux;
		cin.getline(ordaux,10000);
		ca = ordaux;
		map<long long int,order>::iterator it = ordermap.find(did);
		if(it==ordermap.end()){
			order neworder(id,em,ad,ci,st,zi,ca);
			ordermap[did] = neworder;
		}
		else
			it->second.add(id,em,ad,ci,st,zi,ca);
	}
	
	for(int i=0;i<fraudreg.size()-1;i++)
		cout << fraudreg[i] << ',';
	
	cout << fraudreg[fraudreg.size()-1] << endl;
	
	return 0;
}
		
	
