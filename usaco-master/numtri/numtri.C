/*
ID: nissan.po1
LANG: C++
TASK: numtri
*/
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  int rows, tri[1001][1001];
  ofstream out("numtri.out");
  ifstream in("numtri.in");
  in >> rows;
  for (int i=1; i<=rows; i++) {
    for (int j=1; j<=i; j++) {
      in >> tri[i][j];
    }
  }
  for (int i=rows-1; i>0; i--) {
    for (int j=1; j<=i+1; j++) {
      tri[i][j] += (tri[i+1][j] > tri[i+1][j+1] ? tri[i+1][j] : tri[i+1][j+1]);
    }
  }
  out << tri[1][1] << endl;
  in.close(); out.close(); 
}
