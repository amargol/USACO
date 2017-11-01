/*
ID: nissan.po1
LANG: C++
TASK: holstein
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

#define MAX_SCOOPS 1001
int V, G;
int curMin = MAX_SCOOPS;
vector<int> req, curSoln;
vector< vector<int> > feeds;

void printVec(const vector<int>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << (i != vec.size()-1 ? " " : "\n");
  }
}

void seek(int index, vector<int> soln, vector<int> state) {
  soln.push_back(index);
  for (int i = 0; i < V; ++i) {
    state[i] -= feeds[index][i];
  }

  bool done = true;
  for (int i = 0; i < state.size(); ++i) {
    if (state[i] > 0) {
      done = false;
      break;
    }
  }
  if (done && soln.size() < curMin) {
    curMin = soln.size();
    curSoln = soln;
    return;
  }

  for (int i = index+1; i < G; ++i) {
    seek(i, soln, state);
  }
}

int main() {
  ifstream in("holstein.in");
  in >> V;

  req = vector<int>(V);
  for (int i = 0; i < V; ++i) {
    in >> req[i];
  }

  in >> G;
  feeds = vector< vector<int> >(G);
  for (int i = 0; i < G; ++i) {
    vector<int>& v = feeds[i];
    for (int j = 0, f; j < V; ++j) {
      in >> f;
      v.push_back(f);
    }
  }

#if 0
  printVec(req);
  for (int i = 0; i < feeds.size(); ++i) {
    printVec(feeds[i]);
  }
#endif

  for (int i = 0; i < G; ++i) {
    vector<int> v;
    vector<int> state = req;
    seek(i, v, state);
  }

  ofstream out("holstein.out");
  out << curSoln.size() << " ";
  for (int i = 0; i < curSoln.size(); ++i) {
    out << curSoln[i]+1 << (i != curSoln.size()-1 ? " " : "\n");
  }
}
