/*
ID: nissan.po1
LANG: C++
TASK: hamming
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

#define MAX_NUM 256

int numberOfSetBits(int i) {
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int hammingDistance(int x, int y) {
  return numberOfSetBits(x ^ y);
}

map<int, vector<int> > hash;

bool check(int j, const vector<int>& v, int D) {
  for (int i = 0; i < v.size(); ++i) {
    if (hammingDistance(j, v[i]) < D) {
      return false;
    }
  }
  return true;
}

int main() {
  int N, B, D;
  ifstream in("hamming.in");
  in >> N >> B >> D;

  for (int i = 0; i < MAX_NUM; ++i) {
    hash[i].push_back(i);
    for (int j = 0; j < MAX_NUM; ++j) {
      if (check(j, hash[i], D)) {
        hash[i].push_back(j);
      }
    }
  }

  ofstream out("hamming.out");
  for (map<int, vector<int> >::const_iterator it = hash.begin(); it != hash.end(); ++it) {
    const vector<int>& v = it->second;
//    cout << "i: " << it->first << " size: " << it->second.size() << endl;
    if (v.size() >= N) {
      for (int i = 0; i < N; ++i) {
        out << v[i] << (((i+1) % 10 || !v[i]) && i != N-1 ? " " : "\n");
      }
      break;
    }
  }

  return 0;
}
