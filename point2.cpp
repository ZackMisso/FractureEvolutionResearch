#include "point2.h"

Point2::Point2() {
  xpos = 0.0f;
  ypos = 0.0f;
}

Point2::Point2(float x,float y) {
  xpos = x;
  ypos = y;
}

bool Point2::equals(Point other) {
  return xpos == other.xpos && ypos == other.ypos;
}

void Point2::setXpos(float param) {
  xpos = param;
}

void Point2::setYpos(float param) {
  ypos = param;
}
