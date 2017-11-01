/*
ID: nissan.po1
LANG: C++
TASK: runround
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;
typedef unsigned long ulong;

string toStr(ulong num) {
  static stringstream ss;
  ss.str("");
  ss << num;
  return ss.str();
}

bool isRunRound(ulong num) {
  const string s = toStr(num);
  const int len = s.length();
  if (s.find('0') != string::npos) {
    return false;
  }
  int i = 0;
  vector<bool> posVisited(len, 0);
  bool digitVisited[10];
  memset(digitVisited, 0, sizeof(digitVisited));
  do {
    posVisited[i] = true;
    int nmove = s[i] - '0';
    if (digitVisited[nmove]) {
      return false;
    } else {
      digitVisited[nmove] = true;
    }
    i = (i + nmove) % len;
  } while (i != 0 && !posVisited[i]);

  if (i != 0) {
    return false;
  }
  for (int i = 0; i < posVisited.size(); ++i) {
    if (!posVisited[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int M;
  ifstream in("runround.in");
  in >> M;
  do {
    ++M;  
  } while (!isRunRound(M));

  ofstream out("runround.out");
  out << M << endl;
}
