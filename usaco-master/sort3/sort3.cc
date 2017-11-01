/*
ID: nissan.po1
LANG: C++
TASK: sort3
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

int main() {
  ifstream in("sort3.in");
  int N;
  in >> N;

  int a1 = 0, a2 = 0, a3 = 0;
  vector<int> vec(N);
  for (int i = 0; i < N; ++i) {
    in >> vec[i];
    if (vec[i] == 1) a1++;
    if (vec[i] == 2) a2++;
    if (vec[i] == 3) a3++;
  }
  
  int a[3][3];
  memset(a, 0, sizeof(a));
  for (int i = 0; i < a1; ++i) {
    a[0][vec[i]-1]++;
  }
  for (int i = 0; i < a2; ++i) {
    a[1][vec[i+a1]-1]++;
  }
  for (int i = 0; i < a3; ++i) {
    a[2][vec[i+a1+a2]-1]++;
  }

  int total = min(a[0][1], a[1][0]) + min(a[1][2], a[2][1]) + min(a[0][2], a[2][0]) +
              abs(a[0][1] - a[1][0])*2;
  ofstream out("sort3.out");
  out << total << endl;
  out.close();

  return 0;
}
