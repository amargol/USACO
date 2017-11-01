/*
ID: nissan.po1
LANG: C++
TASK: contact
*/
#include <fstream>
#include <iostream>

using namespace std;
typedef unsigned int uint;

struct pat {
  int count;
  string pattern;
};

int compare(const void* a, const void* b) {
  return ((pat*)b)->count - ((pat*)a)->count;
}

// convert binary string to decimal
int hash(const string pattern) {
  char* pEnd;
  return strtoul(pattern.c_str(), &pEnd, 2);
}

int main() {
  ofstream out("contact.out");
  ifstream in("contact.in");
  uint min, max, num, last;
  string seq = "";
  char line[81];;
  in >> min >> max >> num;
  while (!in.eof()) {
    in.getline(line,81);
    seq += line;
  }
  string pattern = "1";
  for (uint i=0; i<max; i++) pattern += "1";
  last = hash(pattern);
  pat vec[last+1];
  pat temp;
  temp.pattern = "";
  temp.count = 0;
  for (uint i=0; i<last+1; i++) vec[i]=temp;
  for (uint i=0; i<seq.size(); ++i) {
    pattern = "";
    for (uint j=0; j<min-1 && i+j<seq.size(); ++j) {
      pattern += seq.at(i+j);
    }
    for (uint j=min-1; j<max && i+j<seq.size(); ++j) {
      pattern += seq.at(i+j);
      if (vec[hash("1"+pattern)].count == 0) {
        temp.pattern = pattern;
        temp.count = 1;
        vec[hash("1"+pattern)] = temp;
      }
      else vec[hash("1"+pattern)].count += 1;
    }
  }
  qsort(vec, last+1, sizeof(pat), compare);
  uint count = 1, pos = 1;
  out << vec[0].count << endl;
  out << vec[0].pattern << (vec[0].count == vec[1].count ? " " : "\n");
  for (uint i=1; i<last+1; i++) {
    if (vec[i].count == vec[i-1].count) {
      out << (++pos % 6 == 1 ? "\n" : "") << vec[i].pattern;
      if (pos % 6 == 0) out << (vec[i].count == vec[i+1].count ? "" : "\n");
      else out << (vec[i].count == vec[i+1].count ? " " : "\n");
    }
    else {
      count++;
      if (count > num || vec[i].count==0) break;
      pos = 1;
      out << vec[i].count << endl;
      out << vec[i].pattern << (vec[i].count == vec[i+1].count ? " " : "\n");
    }
  }
  in.close(); out.close(); 
}
