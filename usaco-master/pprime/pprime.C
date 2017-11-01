/*
ID: nissan.po1
LANG: C++
TASK: pprime
*/
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int num) {
  bool flag = true;
  for (int i=3; i*i<=num; i+=2) {
    if (num % i == 0) {
      flag = false;
      break;
    }
  }
  return flag;
}

/* NOTE: there can be no prime palindromes with an even number of digits
 * otherwise, it's divisible by 11 
 */

void gen3digit(vector<int>& pList) {
  int palindrome;
  for (int d1 = 1; d1 <= 9; d1+=2) {  /* only odd; evens aren't so prime */
    for (int d2 = 0; d2 <= 9; d2++) {
      palindrome = 100*d1 + 10*d2 + d1;
      if (isPrime(palindrome)) {
        pList.push_back(palindrome);
      }
    }
  }
}

void gen5digit(vector<int>& pList) {
  int palindrome;
  for (int d1 = 1; d1 <= 9; d1+=2) {  /* only odd; evens aren't so prime */
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        palindrome = 10000*d1 + 1000*d2 +100*d3 + 10*d2 + d1;
        if (isPrime(palindrome)) {
          pList.push_back(palindrome);
        }
      }
    }
  }
}

void gen7digit(vector<int>& pList) {
  int palindrome;
  for (int d1 = 1; d1 <= 9; d1+=2) {  /* only odd; evens aren't so prime */
    for (int d2 = 0; d2 <= 9; d2++) {
      for (int d3 = 0; d3 <= 9; d3++) {
        for (int d4 = 0; d4 <= 9; d4++) {
          palindrome = 1000000*d1 + 100000*d2 +10000*d3 + 1000*d4 + 100*d3 + 10*d2 + d1;
          if (isPrime(palindrome)) {
            pList.push_back(palindrome);
          }
        }
      }
    }
  }
}

int main() {
  ofstream out("pprime.out");
  ifstream in("pprime.in");
  int min, max;
  in >> min >> max;
  vector<int> pList;
  pList.push_back(5);
  pList.push_back(7);
  pList.push_back(11);
  if (max < 10000) {
    gen3digit(pList);
  }
  else if (max < 1000000) {
    gen3digit(pList);
    gen5digit(pList);
  }
  else {
    gen3digit(pList);
    gen5digit(pList);
    gen7digit(pList);
  }
  for (unsigned int i=0; i<pList.size(); ++i) {
    if (pList[i] >= min && pList[i] <= max) {
      out << pList[i] << endl;
    }
  }
  in.close();
  out.close();
} 
