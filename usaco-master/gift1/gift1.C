/*
ID: nissan.po1
LANG: C++
TASK: gift1
*/
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
  ofstream outStream_n("gift1.out");
  ifstream inStream_n("gift1.in");
  map<string, int> startMap_n; // map of person to initial balance
  map<string, int> endMap_n; // map of person to final balance
  string people_an[10]; // maintain unsorted order of persons
  int numPeople_i = 0;
  inStream_n >> numPeople_i;
  
  string currName_n = "";
  for (int i=0; i<numPeople_i; ++i) {
    inStream_n >> currName_n;
    people_an[i] = currName_n;
    startMap_n[currName_n] = 0;
    endMap_n[currName_n] = 0;
  }
  int money_i = 0;
  int recipients_i = 0;
  for (int i=0; i<numPeople_i; ++i) {
    inStream_n >> currName_n >> money_i >> recipients_i;
    startMap_n[currName_n] = money_i;
    if ( 0 == recipients_i ) {
      endMap_n[currName_n] += money_i;
    }
    //else if ( 0 != money_i ) {
    else {
      endMap_n[currName_n] += money_i % recipients_i;
      for (int j=0; j<recipients_i; ++j) {
        inStream_n >> currName_n;
        endMap_n[currName_n] += (money_i / recipients_i);
      }
    }
  }
  for (int i=0; i<numPeople_i; ++i) {
    //cout << people_an[i] << " start: " << startMap_n[people_an[i]] << endl;
    //cout << people_an[i] << " end: " << endMap_n[people_an[i]] << endl;
    outStream_n
      << people_an[i] << " "
      << endMap_n[people_an[i]] - startMap_n[people_an[i]] << endl;
  }
  outStream_n.close();
  inStream_n.close();
}
