/*
ID: nissan.po1
LANG: C++
TASK: subset
*/
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

typedef unsigned long ulong;

ulong f(int n, int k) {
  static map<ulong, map<ulong, ulong> > cache;
  if (n < 0 || k < 0) {
    return 0;
  }
  if (n == 0 && k == 0) {
    return 1;
  }

  if (cache.find(n) != cache.end() && cache[n].find(k) != cache[n].end()) {
    return cache[n][k];
  }
  return cache[n][k] = f(n, k-1) + f(n-k, k-1);
}

int main() {
  int N;
  ifstream in("subset.in");
  ofstream out("subset.out");
  in >> N;

  const int sumToN = N*(N+1)/2;
  if (sumToN % 2 == 1) {
    out << 0 << endl;
    return 0;
  }

  const int halfSum = sumToN / 2;
  out << f(halfSum, N)/2l << endl;

  return 0;
}
