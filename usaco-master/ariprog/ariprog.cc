/*
ID: nissan.po1
LANG: C++
TASK: ariprog
*/
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_N 250
#define LIMIT MAX_N * MAX_N * 2

int main() {
  int N, M;
  ifstream in("ariprog.in");
  in >> N >> M;
  in.close();

  bool HASH[LIMIT + 1];
  memset(HASH, 0, sizeof(HASH));

  // pre-compute all the bisquares
  set<int> bisquares;
  for (int i = 0; i <= M; ++i) {
    for (int j = 0; j <= M; ++j) {
      const int bisquare = i*i + j*j;
      bisquares.insert(bisquare);
      HASH[bisquare] = true;
    }
  }

  // convert set to vector
  vector<int> vec;
  vec.reserve(bisquares.size());
  copy(bisquares.begin(), bisquares.end(), back_inserter(vec));

  // find all the arithmetic progressions
  map<int, list<int> > results;
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = i+1; j < vec.size(); ++j) {
      const int diff = vec[j] - vec[i];
      bool hasSeq = true;
      for (int n = 2; n < N; ++n) {
        const int next = vec[i] + n*diff;
        if (next > LIMIT || !HASH[next]) {
          hasSeq = false;
          break;
        }
      }
      if (hasSeq) {
        results[diff].push_back(vec[i]);
      }
    }
  }

  // print results, sorted by smallest difference first
  ofstream out("ariprog.out");
  if (results.empty()) {
    out << "NONE" << endl;
  } else {
    for (map<int, list<int> >::const_iterator it = results.begin(); it != results.end(); ++it) {
      for (list<int>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        out << *it2 << " " << it->first << endl;
      }
    }
  }
  out.close();

  return 0;
}
