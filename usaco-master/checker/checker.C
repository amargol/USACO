/*
ID: nissan.po1
LANG: C++
TASK: checker
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ofstream out("checker.out");
ifstream in("checker.in");
int size, solutions=0, ok_row[14], ok_ldiag[28], ok_rdiag[28], board[14][14];

int pos_of_queen(int col) {
  for (int row=1; row<=size; ++row) {
    if (board[row][col]) {
      return row;
    }
  }
}

void place_queen(int col) {
  if (col == size+1) {
    // got a solution!
    if (solutions < 3) { // only need to keep track of first 3 answers
      int i;
      for (i=1; i<size; ++i) {
         out << pos_of_queen(i) << " ";
      }
      out << pos_of_queen(i) << endl;
    }
    solutions += 1; // increment total number of answers
    return;
  }
  for (int row=1; row<=size; ++row) {
    if (ok_row[row]) {
      // only need to check diagonals in here
      int v1 = row-col+size;
      int v2 = row+col;
      if (ok_ldiag[v1] && ok_rdiag[v2]) {
        ok_row[row] = ok_ldiag[v1] = ok_rdiag[v2] = 0;
        board[row][col] = 1; // mark queen at square
        place_queen(col+1);
        // recursion failed; free up marked squares
        board[row][col] = 0;
        ok_row[row] = ok_ldiag[v1] = ok_rdiag[v2] = 1;
      }
    }
  }
}

int main() {
  int i,limit;
  in >> size;

  // reset board
  for (i=0; i<=size; ++i) ok_row[i] = ok_ldiag[i] = ok_rdiag[i] = 1; 
  for (i=size+1; i<=2*size; ++i) ok_ldiag[i] = ok_rdiag[i] = 1;

  // main loop
  if (size == 6) { limit = size; }
  else { limit = size/2; }
  for (int row=1; row<=limit; ++row) {
    if (ok_row[row]) {
      int v1 = row-1+size;
      int v2 = row+1;
      if (ok_ldiag[v1] && ok_rdiag[v2]) {
        ok_ldiag[v1] = ok_rdiag[v2] = 0;
        ok_row[row] = 0;
        board[row][1] = 1;
        place_queen(2);
        board[row][1] = 0;
        ok_row[row] = 1;
        ok_ldiag[v1] = ok_rdiag[v2] = 1;
      }
    }
  } 
  if (size % 2) {
    int temp = solutions;
    int mid = (size/2) + 1;
    if (ok_row[mid]) {
      int v1 = mid-1+size;
      int v2 = mid+1;
      if (ok_ldiag[v1] && ok_rdiag[v2]) {
        ok_ldiag[v1] = ok_rdiag[v2] = 0;
        ok_row[mid] = 0;
        board[mid][1] = 1;
        place_queen(2);
        board[mid][1] = 0;
        ok_row[mid] = 1;
        ok_ldiag[v1] = ok_rdiag[v2] = 1;
      }
    }
    int extra = solutions - temp;
    solutions -= extra;
    out << solutions*2 + extra << endl;
  }
  else if (size != 6) out << solutions*2 << endl;
  else out << solutions << endl;
  in.close(); out.close();
}
