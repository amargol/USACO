/*
ID: nissan.po1
LANG: C++
TASK: ride
*/
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ofstream outStream_n("ride.out");
  ifstream inStream_n("ride.in");
  string cometName_n = "";
  string groupName_n = "";
  inStream_n >> cometName_n >> groupName_n;
  int cometNumber_i = 1;
  int groupNumber_i = 1;
  for (unsigned int i=0; i<cometName_n.length(); ++i) {
    cometNumber_i *= (cometName_n.at(i) - 64);
  }
  for (unsigned int i=0; i<groupName_n.length(); ++i) {
    groupNumber_i *= (groupName_n.at(i) - 64);
  }
  if ((groupNumber_i % 47) == (cometNumber_i % 47)) {
    outStream_n << "GO" << endl;
  }
  else {
    outStream_n << "STAY" << endl;
  }
  outStream_n.close();
  inStream_n.close();
}
