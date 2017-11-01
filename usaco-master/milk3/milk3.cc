/*
ID: nissan.po1
LANG: C++
TASK: milk3
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;

struct State {
  State() {}

  State(int _A, int _B, int _C) {
    b[0] = pair<int,int>(_A, 0);
    b[1] = pair<int,int>(_B, 0);
    b[2] = pair<int,int>(_C, _C);
  }

  bool pour(int i, int j) {
    if (b[i].second == 0) return false;

    int amt = min(b[i].second, b[j].first - b[j].second);
    b[j].second += amt;
    b[i].second -= amt;
    return true;
  }

  pair<int,int> b[3];
  int hash() { return b[0].second*10000 + b[1].second*100 + b[2].second; }
};

set<int> res;
map<int, State> visited;

void seek(State s) {
  if (visited.find(s.hash()) != visited.end()) {
    return;
  }
  visited[s.hash()] = s;
  
  if (s.b[0].second == 0) {
    res.insert(s.b[2].second);
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      State ss = s; // copy
      if (i == j || !ss.pour(i, j)) continue;
      seek(ss);
    }
  }
}

int main() {
  ifstream in("milk3.in");
  int A, B, C;
  in >> A >> B >> C;
  State s(A, B, C);
  seek(s);

  ofstream out("milk3.out");
  for (set<int>::const_iterator it = res.begin(); it != res.end(); ++it) {
    out << (it != res.begin() ? " " : "") << *it;
  }
  out << endl;

  return 0;
}

