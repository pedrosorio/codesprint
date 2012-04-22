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

int main() {
  string classes[19] = {
    "Advertising",
    "Car and truck",
    "Contractors and freelancers",
    "Cost of Goods Sold",
    "Credit Card Payment",
    "Duplicate or Wrong Expenses",
    "Estimated and Income Tax Payments",
    "Meals & entertainment",
    "Mileage",
    "Office Supplies",
    "Other expenses",
    "Owner's Pay/Draw",
    "Personal Expense",
    "Sales Tax Submitted",
    "Supplies",
    "Transfer Out",
    "Travel",
    "Uncategorized",
    "Utilities"};
  
  int N; 
  cin >> N;
  string s;
  vector<string> sout(3*N);
  for(int i=0;i<N;i++) {
    cin >> s;
    string name,tags,clasf;
    size_t found;
    found=s.find("CLICK-TO-PAY");
    if(found!=string::npos) {
      name="Click-to-pay";
      tags="Credit Card, Payment";
    }
    found=s.find("APPLE ONLINE STORE");
    if(found!=string::npos) {
      name="Apple Online Store";
      tags="Apple, Store";
    }
    found=s.find("AGILE WEB SOLUTIONS");
    if(found!=string::npos)
      name="agilebits.com";   
    found=s.find("FOREIGN TRANSACTION FEE");
    if(found!=string::npos)
      name="Credit Card Foreign Transaction Fee";   
    found=s.find("LATE FEE");
    if(found!=string::npos)
      name="Late Fee";   
    found=s.find("WOOT.COM ");
    if(found!=string::npos)
      name="Woot.com";   
    found=s.find("FRESHBOOKS");
    if(found!=string::npos)
      name="Freshbooks";   
    found=s.find("STEVENSACKS");
    if(found!=string::npos)
      name="Steven Sacks";   
    found=s.find("MI RANCHITO");
    if(found!=string::npos)
      name="Mi Ranchito";   
    found=s.find("O'REILLY MEDIA");
    if(found!=string::npos)
      name="O'Reilly Media";   
    found=s.find("DREAMHOST.COM");
    if(found!=string::npos)
      name="DreamHost";   
    found=s.find("Panic");
    if(found!=string::npos)
      name="Panic.com";   
    found=s.find("ADOBE SYSTEMS");
    if(found!=string::npos)
      name="Adobe";   
    found=s.find("SIT4LESS.COM");
    if(found!=string::npos)
      name="Sit4Less.com";   
    found=s.find("LYNDA.COM");
    if(found!=string::npos)
      name="Lynda.com";   
    found=s.find("ALFRED");
    if(found!=string::npos)
      name="Alfred";   
    found=s.find("APPLE ONLINE STORE");
    if(found!=string::npos)
      name="Click-to-pay";   
    found=s.find("APPLE ONLINE STORE");
    if(found!=string::npos)
      name="Click-to-pay";   
    sout[i]=name;
  }
  for(int i=0;i<3*N;i++)
    cout << sout[i] << endl;
  
  
  return 0;
}
