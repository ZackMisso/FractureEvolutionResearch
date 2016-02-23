#include "edge3.h"

Edge3::Edge3() {
  first.xpos = 0.0f;
  first.ypos = 0.0f;
  first.zpos = 0.0f;
  second.xpos = 0.0f;
  second.ypos = 0.0f;
  second.zpos = 0.0f;
}

Edge3::Edge3(Point3 one,Point3 two) {
  first.xpos = one.xpos;
  first.ypos = one.ypos;
  first.zpos = one.zpos;
  second.xpos = two.xpos;
  second.ypos = two.ypos;
  second.zpos = two.zpos;
}

Edge3::Edge3(float x,float y,float z,float xx,float yy,float zz) {
  first.xpos = x;
  first.ypos = y;
  first.zpos = z;
  second.xpos = xx;
  second.ypos = yy;
  second.zpos = zz;
}

Point3 Edge3::getFirst() { return first; }
Point3 Edge3::getSecond() { return second; }

void Edge3::setFirst(Point3 param) { first = param; }
void Edge3::setSecond(Point3 param) { second = param; }
