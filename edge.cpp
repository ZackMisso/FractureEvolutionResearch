#include "edge.h"

Edge::Edge(Point2 one,Point2 two) {
  first.xpos = one.xpos;
  first.ypos = one.ypos;
  second.xpos = two.xpos;
  second.ypos = two.ypos;
}

Edge::Edge(float x,float y,float xx,float yy) {
  first.xpos = x;
  first.ypos = y;
  second.xpos = xx;
  second.ypos = yy;
}

Point2 Edge::getFirst() { return first; }
Point2 Edge::getSecond() { return second; }

void Edge::setFirst(Point2 point) {
  first.xpos = point.xpos;
  first.ypos = point.ypos;
}

void Edge::setSecond(Point2 point) {
  second.xpos = point.xpos;
  second.ypos = point.ypos;
}
