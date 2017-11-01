/*
ID: nissan.po1
LANG: C++
TASK: clock
*/
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;
typedef unsigned int uint;

string o_clock = " o'clock";
string quarter_past = "Quarter past ";
string quarter_to = "Quarter to ";

string english(int num) {
  switch (num) {
    case 1: return "one";
    case 2: return "two";
    case 3: return "three";
    case 4: return "four";
    case 5: return "five";
    case 6: return "six";
    case 7: return "seven";
    case 8: return "eight";
    case 9: return "nine";
    case 10: return "ten";
    case 11: return "eleven";
    case 12: return "twelve";
    case 13: return "thirteen";
    case 14: return "fourteen";
    case 15: return "fifteen";
    case 16: return "sixteen";
    case 17: return "seventeen";
    case 18: return "eighteen";
    case 19: return "nineteen";
    case 20: return "twenty";
    case 30: return "thirty";
    case 40: return "forty";
    case 50: return "fifty";
  }
}

string capitalize(string s) {
  string result = "";
  result += toupper(s.at(0));
  for (uint i=1; i<s.length(); ++i) {
    result += s.at(i);
  }
  return result;
}

int main() {
  ofstream out("clock.out");
  ifstream in("clock.in");
  int hours, mins;
  char c;
  in >> hours >> c >> mins;
  if (mins == 0) out << capitalize(english(hours)) << o_clock << endl;
  else if (mins == 15) out << quarter_past << english(hours) << endl;
  else if (mins == 30) out << capitalize(english(hours)) << " " << english(mins) << endl;
  else if (mins == 45) out << quarter_to << english( (hours+1 > 12 ? 1 : hours+1) ) << endl;
  else if (mins < 45)
    out << capitalize(english(hours)) << " "
        << ((mins % 10 == 0 || mins < 20) ? english(mins) : english(mins - (mins % 10)) + "-" + english(mins % 10)) << endl;
  else {
    mins = 60 - mins;
    out << capitalize(english(mins)) << " to "
        << english( (hours+1 > 12 ? 1 : hours+1) ) << endl;
  }
  in.close(); out.close();   
}
