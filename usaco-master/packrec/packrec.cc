/*
ID: nissan.po1
LANG: C++
TASK: packrec
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <list>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 4
#define max3(a,b,c) max(max(a,b), c)
#define max4(a,b,c,d) max(max3(a,b,c), d)

struct Rectangle {
  int w;
  int l;
  bool operator<(const Rectangle& other) const {
    return w < other.w;
  }
  bool operator==(const Rectangle& other) const {
    return other.w == w && other.l == l;
  }

  void rotate() {
    int tmp = l;
    l = w;
    w = tmp;
  }
};

Rectangle rect[MAXN];
int perm[24][4] = {
  {0,1,2,3},
  {0,1,3,2},
  {0,2,1,3},
  {0,2,3,1},
  {0,3,1,2},
  {0,3,2,1},
  {1,0,2,3},
  {1,0,3,2},
  {1,2,0,3},
  {1,2,3,0},
  {1,3,0,2},
  {1,3,2,0},
  {2,0,1,3},
  {2,0,3,1},
  {2,1,0,3},
  {2,1,3,0},
  {2,3,0,1},
  {2,3,1,0},
  {3,0,1,2},
  {3,0,2,1},
  {3,1,0,2},
  {3,1,2,0},
  {3,2,0,1},
  {3,2,1,0}
};

int curMin = 99999999;
set<Rectangle> soln;

void check(int w, int l) {
  if (w > l) {
    int tmp = l;
    l = w;
    w = tmp;
  }

  Rectangle rec;
  rec.w = w;
  rec.l = l;
  const int area = w*l;
  if (area < curMin) { // new min
    soln.clear();
    curMin = area;
    soln.insert(rec);
  } else if (area == curMin) {
    soln.insert(rec);
  }
}

void computeMin() {
  for (int p = 0; p < 24; ++p) {
    Rectangle r0 = rect[perm[p][0]],
              r1 = rect[perm[p][1]],
              r2 = rect[perm[p][2]],
              r3 = rect[perm[p][3]];

    for (int a = 0; a < 2; ++a, r0.rotate()) {
      for (int b = 0; b < 2; ++b, r1.rotate()) {
        for (int c = 0; c < 2; ++c, r2.rotate()) {
          for (int d = 0; d < 2; ++d, r3.rotate()) {
            int w[6], l[6];

            w[0] = r0.w + r1.w + r2.w + r3.w;
            l[0] = max4(r0.l, r1.l, r2.l, r3.l);
            check(w[0], l[0]);

            w[1] = max(r0.l, r1.w + r2.w + r3.w);
            l[1] = r0.w + max3(r1.l, r2.l, r3.l);
            check(w[1], l[1]);

            w[2] = r3.w + max(r0.l, r1.w + r2.w);
            l[2] = max(r3.l, r0.w + max(r1.l, r2.l));
            check(w[2], l[2]);

            w[3] = r0.w + max(r1.w, r2.w) + r3.w;
            l[3] = max3(r0.l, r1.l + r2.l, r3.l);
            check(w[3], l[3]);

            w[4] = max(r0.w, r1.w) + r2.w + r3.w;
            l[4] = max3(r0.l + r1.l, r2.l, r3.l);
            check(w[4], l[4]);

            w[5] = r0.w + r3.w;
            if (r0.l < r3.l)
              w[5] = max(r0.w + r3.w, r1.w + r3.w);
            if (r0.l + r1.l > r3.l)
              w[5] = max(w[5], r1.w + r2.w);
            if (r0.l > r3.l)
              w[5] = max(w[5], r0.w + r2.w);

            w[5] = max3(w[5], r1.w, r2.w);
            l[5] = max(r0.l + r1.l, r2.l + r3.l);
            check(w[5], l[5]);
          }
        }
      }
    }
  }
}

int main() {
  ifstream in("packrec.in");
  for (int i = 0; i < MAXN; ++i) {
    in >> rect[i].w >> rect[i].l;
  }

  computeMin();

  ofstream out("packrec.out");
  out << curMin << endl;
  for (set<Rectangle>::const_iterator it = soln.begin(); it != soln.end(); ++it) {
    out << it->w << " " << it->l << endl;
  }
}
