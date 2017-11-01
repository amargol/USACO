/*
ID: nissan.po1
LANG: C++
TASK: sprime
*/
#include <fstream>
#include <iostream>

using namespace std;

int num_digits;
ofstream out("sprime.out");
ifstream in("sprime.in");

bool prime(int num);

void sprime(int digit, int num) {
   digit++;
   if (prime(num)) {
     if (digit == num_digits) {
       // found a super prime
       out << num << endl;
       return;
     }
     sprime(digit, num*10 + 1);
     sprime(digit, num*10 + 3);
     sprime(digit, num*10 + 7);
     sprime(digit, num*10 + 9);
   }
}

bool prime(int num) {
  if (num == 2) return true;
  for (int i=3; i*i<=num; i+=2) {
    if (num % i == 0) return false;
  }
  return true;
}

int main() {
  in >> num_digits;
  sprime(0, 2);
  sprime(0, 3);
  sprime(0, 5);
  sprime(0, 7);
  in.close(); out.close();
}
