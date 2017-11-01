/*
ID: nissan.po1
LANG: C++
TASK: milk
*/
#include <fstream>
#include <iostream>
using namespace std;

struct farmer {
  int price;
  int amtOfMilk;
};

int main() {
  ofstream out("milk.out");
  ifstream in("milk.in");
  int total = 0;
  int amt, numFarmers;
  in >> amt >> numFarmers;
  farmer fList[5000];
  for (int i=0; i<numFarmers; ++i) {
    in >> fList[i].price >> fList[i].amtOfMilk;
  }
  // sort list of farmers according to price
  int cheapest;
  for (int i=0; i<numFarmers; ++i) {
    cheapest = i;
    for (int j=i+1; j<numFarmers; ++j) {
      if (fList[j].price < fList[cheapest].price) {
        cheapest = j;
      }
    }
    // swap elements
    farmer temp = fList[i];
    fList[i] = fList[cheapest];
    fList[cheapest] = temp;
  }
  for (int i=0; i<numFarmers; ++i) {
    if (fList[i].amtOfMilk <= amt) {
      amt -= fList[i].amtOfMilk;
      total += (fList[i].amtOfMilk * fList[i].price);
    }
    else {
      // got all the milk needed
      total += (fList[i].price * amt);
      break;
    }
  }
  out << total << endl;
  in.close();
  out.close();
}
