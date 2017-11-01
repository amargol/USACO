/*
ID: nissan.po1
LANG: C++
TASK: rect1
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
typedef unsigned int uint;

struct rect{
  uint llx;
  uint lly;
  uint urx;
  uint ury;
  uint color;
};

list<rect> rect_queue; // list of rects that needs to be processed
vector<rect> rect_list; // list of rects obtained from input
vector<rect> main_list; // list of rects as seen on paper

// splits the first rect if it intersects the second
void split_rects(const rect r1, const rect r2) {
  rect temp;
  temp.color = r1.color;
  // left
  if (r1.llx < r2.llx) {
    temp.llx = r1.llx;
    temp.lly = r1.lly;
    temp.urx = (r1.urx<r2.llx ? r1.urx : r2.llx);
    temp.ury = r1.ury;
    rect_queue.push_back(temp);
  }
  // right
  if (r1.urx > r2.urx) {
    temp.llx = (r1.llx>r2.urx? r1.llx : r2.urx);
    temp.lly = r1.lly;
    temp.urx = r1.urx;
    temp.ury = r1.ury;
    rect_queue.push_back(temp);
  }
  // top
  if (r1.ury > r2.ury) {
    temp.llx = (r1.llx>r2.llx ? r1.llx : r2.llx);
    temp.lly = (r1.lly>r2.ury ? r1.lly : r2.ury);
    temp.urx = (r1.urx<r2.urx ? r1.urx : r2.urx);
    temp.ury = r1.ury;
    rect_queue.push_back(temp);
  }
  // bottom
  if (r1.lly < r2.lly) {
    temp.llx = (r1.llx>r2.llx ? r1.llx : r2.llx);
    temp.lly = r1.lly;
    temp.urx = (r1.urx<r2.urx ? r1.urx : r2.urx);
    temp.ury = (r1.ury<r2.lly ? r1.ury : r2.lly);
    rect_queue.push_back(temp);
  }
}

bool intersects(const rect r1, const rect r2) {
  return !(r1.urx <= r2.llx || r1.llx >= r2.urx || r1.lly >= r2.ury || r1.ury <= r2.lly);
}
      
void check_rect(rect curr) {
  rect temp;
  if (main_list.empty()) {
    return main_list.push_back(curr);
  }
  bool flag = false;
  for (uint i=0; i<main_list.size(); ++i) {
    if (intersects(curr, main_list.at(i))) {
      split_rects(curr, main_list.at(i));
      while (!rect_queue.empty()) {
        temp = rect_queue.front();
        rect_queue.pop_front();
        check_rect(temp);
      }
      flag = true;
      break;
    }
  }
  if (!flag) {
    main_list.push_back(curr);
  }
}

int main() {
  ofstream out("rect1.out");
  ifstream in("rect1.in");
  uint length, width, num_rects, total = 0;
  int color_count[2501];
  for (int i=0; i<2501; ++i) {
    color_count[i]=0;
  }
  rect curr;
  in >> length >> width >> num_rects;
  for (uint i=0; i<num_rects; ++i) {
    in >> curr.llx >> curr.lly >> curr.urx >> curr.ury >> curr.color;
    rect_list.push_back(curr);
  }
  for (uint i=num_rects; i>0; --i) {
    check_rect(rect_list.at(i-1));
  }
  for (uint i=0; i<main_list.size(); ++i) {
    curr = main_list.at(i);
    color_count[curr.color] += (curr.urx-curr.llx) * (curr.ury-curr.lly);
    total += (curr.urx-curr.llx) * (curr.ury-curr.lly);
  }
  if (total < length*width) {
    color_count[1] += length*width - total;
  }
  for (uint i=1; i<=2500; ++i) {
    if (color_count[i] > 0) out << i << " " << color_count[i] << endl;
  }
  in.close(); out.close();
}
