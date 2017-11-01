/*
ID: nissan.po1
LANG: C++
TASK: barn1
*/
#include <fstream>
#include <iostream>
using namespace std;

ofstream out("barn1.out");
ifstream in("barn1.in");
unsigned int max_boards, num_stalls, num_cows, stall[201][2], temp;
bool debug=false;

void split_board() {
  unsigned int max, temp, index;
  max = temp = index = 0;
  for (unsigned int i=1; i<=num_stalls; ++i) {
    temp = 0;
    for (unsigned int j=i; j<=num_stalls; ++j) {
      if (stall[j][0] == 0) ++temp; // unoccupied
      else break;
    }
    if (temp >= max) {
      max = temp;
      index = i;
    }
  }
  for (unsigned int i=index; i<index+max; ++i) {
    stall[i][1] = 0; // split board
    stall[i][0] = 2; // mark as being unboarded
  }

  if (debug) {
    cout << "cows: ";
    for (int i=1; i<=num_stalls; ++i) cout << stall[i][0]; cout << endl << "barn: ";
    for (int i=1; i<=num_stalls; ++i) cout << stall[i][1]; cout << endl << endl;
  }
}

int main() {
  in >> max_boards >> num_stalls >> num_cows;
  for (unsigned int i=1; i<=num_stalls; ++i) {
    stall[i][0]=0; // initialize as unoccupied
    stall[i][1]=1; // start with all stalls boarded
  }
  for (unsigned int i=0; i<num_cows; ++i) {
    in >> temp;
    stall[temp][0]=1; // set as occupied
  }

  // split boards at ends if possible
  for (int i=1; i<=num_stalls; ++i) {
    if (stall[i][0] == 0) { stall[i][1]=0; stall[i][0]=2; }
    else break;
  }
  for (int i=num_stalls; i>0; --i) {
    if (stall[i][0] == 0) { stall[i][1]=0; stall[i][0]=2; }
    else break;
  }

  if (debug) {
    cout << "cows: ";
    for (int i=1; i<=num_stalls; ++i) cout << stall[i][0]; cout << endl << "barn: ";
    for (int i=1; i<=num_stalls; ++i) cout << stall[i][1]; cout << endl << endl;
  }

  // split boards to uncover largest gaps
  for (unsigned int i=1; i<max_boards; ++i) split_board();

  temp = 0;
  for (unsigned int i=1; i<=num_stalls; ++i) {
    if (stall[i][1]) ++temp;
  }
  out << temp << endl;
  in.close(); out.close();
}
