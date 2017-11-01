/*
ID: nissan.po1
LANG: C++
TASK: zerosum
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

int N;
set<string> results;

template <class T>
string toStr(T i) {
  static stringstream ss;
  ss.str("");
  ss << i;
  return ss.str();
}

string toStrW(int i) {
  if (i < 10) return toStr(i);

  string s = toStr(i);
  string s2 = s;
  if (i > 10) {
    s2 = s[0];
    for (int ii = 1; ii < s.size(); ++ii) {
      s2 += " " + toStr(s[ii]);
    }
  }
  return s2;
}

bool check(const string& s) {
  for (int i = 1; i <= N; ++i) {
    if (s.find_first_of('0' + i) == string::npos) {
      return false;
    }
  }
  return true;
}

void seek(int i, int sum, string s, int n) {
//  cout << "I: " << i << " SUM: " << sum << " S: " << s << " N: " << n << endl;
  if (i == N+1) {
    if ((sum == 0) && n == N+1 && check(s)) {
      results.insert(s);
    } else if (n != N+1 && abs(sum) == abs(n) && check(s + toStrW(n))) {
      string ss = s + (sum == n ? "-" : "+") + toStrW(n);
      if (ss[0] != '-') results.insert(ss.substr(1));
    }
    return;
  }
  seek(i+1, sum+n, s+"+"+toStrW(n), i);
  seek(i+1, sum-n, s+"-"+toStrW(n), i);
  seek(i+1, sum, s, i == n ? n : n*10+(i));
}

int main() {
  ifstream in("zerosum.in");
  in >> N;
  seek(2, 0, "", 1);
  ofstream out("zerosum.out");
  for (set<string>::const_iterator it = results.begin(); it != results.end(); ++it) {
    out << *it << endl;
  }
}
