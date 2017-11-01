/*
ID: nissan.po1
LANG: C++
TASK: namenum
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

char alphaToDigit(const char c) {
  switch (c) {
    case 'A': case 'B': case 'C': return '2';
    case 'D': case 'E': case 'F': return '3';
    case 'G': case 'H': case 'I': return '4';
    case 'J': case 'K': case 'L': return '5';
    case 'M': case 'N': case 'O': return '6';
    case 'P': case 'R': case 'S': return '7';
    case 'T': case 'U': case 'V': return '8';
    case 'W': case 'X': case 'Y': return '9';
    default: return '0';
  }
}

string nameToSerial(string name) {
  string result = "";
  for (unsigned int i=0; i<name.length(); ++i) {
    result.append(1, alphaToDigit(name.at(i)));
  }
  return result;
}

int main() {
  ofstream out("namenum.out");
  ifstream in("namenum.in");
  ifstream dict("dict.txt");
  string serialNum = "";
  in >> serialNum;
  in.close();
  
  string currName = "";
  vector<string> pNames, names;
  while (!dict.eof()) {
    dict >> currName;
    if (currName.length() == serialNum.length()
        && alphaToDigit(currName.at(0)) == serialNum.at(0)) {
      pNames.push_back(currName);
    }
  }
  for (unsigned int i=0; i<pNames.size(); ++i) {
    if (nameToSerial(pNames[i]) == serialNum) {
      names.push_back(pNames[i]);
    }
  }
  if (names.empty()) {
    out << "NONE" << endl;
  }
  else {
    for (unsigned int i=0; i<names.size(); ++i) {
      out << names[i] << endl;
    }
  }
  out.close();
  dict.close();
}
