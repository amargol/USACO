/*
ID: nissan.po1
LANG: C++
TASK: beads
*/
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ofstream out("beads.out");
  ifstream in("beads.in");
  string beads = "";
  int length = 0;
  in >> length;
  in >> beads;
  in.close();
  string necklace = beads + beads + beads;
  int max = 0;
  int front;
  int back;
  char c;
  for (unsigned int i=beads.length(); i<2*beads.length(); ++i) {
    // -->
    front = 1;
    c = necklace.at(i);
    for (unsigned int j=i+1; j<beads.length()+i; ++j) {
      if (necklace.at(j) == c || necklace.at(j) == 'w') { front += 1; }
      else if (c == 'w') {
        c = necklace.at(j);
        front += 1;
      }
      else { break; }
    }
    // <--
    back = 1;
    c = necklace.at(i-1);
    for (unsigned int j=i-2; j>i-beads.length()-1; --j) {
      if (necklace.at(j) == c || necklace.at(j) == 'w') { back += 1; }
      else if (c == 'w') {
        c = necklace.at(j);
        back += 1;
      }
      else { break; }
    }
    
    if ((front + back) > max) { max = front + back; }
  }
  if (max > length) { max = length; }
  out << max << endl;
  out.close();
}
