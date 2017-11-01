/*
ID: nissan.po1
LANG: C++
TASK: lamps
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;
typedef bitset<100> State_t;

int N, C, ON[100], OFF[100];
set<string> solns;

inline void toggle(State_t& state, int i) {
  state[i] = !state[i];
}

inline bool isBitSet(State_t state, int i) {
  return state[i];
}

string toBinary(State_t x) {
  string s(N, '0');
  for (int i = 0; i < N; ++i) {
    s[i] = (x[i] ? '1' : '0');
  }
  return s;
}

bool visited(State_t state, int c) {
  static map<string, map<int, bool> > m_map;
  bool retval = true;
  const string str = toBinary(state);
  if (!m_map[str][c]) {
    m_map[str][c] = true;
    retval = false;
  }
  return retval;
}

// flip state of all lamps
State_t f1(State_t state) {
  for (int i = 0; i < N; ++i) {
    toggle(state, i);
  }
  return state;
}

// flip odd-numbered lamps
State_t f2(State_t state) {
  for (int i = 0; i < N; ++i) {
    if (i % 2 == 0) {
      toggle(state, i);
    }
  }
  return state;
}

// flip even-numbered lamps
State_t f3(State_t state) {
  for (int i = 0; i < N; ++i) {
    if (i % 2 == 1) {
      toggle(state, i);
    }
  }
  return state;
}

// flip state of 3k+1 lamps
State_t f4(State_t state) {
  for (int i = 0; i < N; ++i) {
    if (i % 3 == 0) {
      toggle(state, i);
    }
  }
  return state;
}

bool checkState(State_t state) {
  for (int i = 0; i < N; ++i) {
    if (ON[i] && !isBitSet(state, i)) {
      return false;
    }
  }
  for (int i = 0; i < N; ++i) {
    if (OFF[i] && isBitSet(state, i)) {
      return false;
    }
  }
  return true;
}

void seek(State_t state, int c) {
//  cout << toBinary(state) <<  " C: " << c << endl;
  if (visited(state, c)) {
    return;
  }
  if (c == 0) {
    if (checkState(state)) {
      solns.insert(toBinary(state));
    }
    return;
  }

  seek(f1(state), c-1);
  seek(f2(state), c-1);
  seek(f3(state), c-1);
  seek(f4(state), c-1);
}

int main() {
  ifstream in("lamps.in");
  in >> N >> C;
  int i;
  while (in >> i) {
    if (i == -1) break;
    ON[i-1] = 1;
  }
  while (in >> i) {
    if (i == -1) break;
    OFF[i-1] = 1;
  }

  State_t state;
  for (int i = 0; i < N; ++i) {
    state[i] = 1;
  }
  seek(state, C);

  ofstream out("lamps.out");
  if (solns.empty()) {
    out << "IMPOSSIBLE" << endl;
  }
  for (set<string>::const_iterator it = solns.begin(); it != solns.end(); ++it) {
    out << *it << endl;
  }

  return 0;
}
