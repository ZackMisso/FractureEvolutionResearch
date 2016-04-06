#include "point2.h"

#include <iostream>
using namespace std;

Point2::Point2() {
  xpos = 0.0f;
  ypos = 0.0f;
}

Point2::Point2(real x,real y) {
  xpos = x;
  ypos = y;
}

bool Point2::equals(Point2 other) {
  return xpos == other.xpos && ypos == other.ypos;
}

Point2 Point2::minus(Point2 other) {
  Point2 result;
  result.xpos = xpos - other.xpos;
  result.ypos = ypos - other.ypos;
  return result;
}

Point2 Point2::add(Point2 other) {
  Point2 result;
  result.xpos = xpos + other.xpos;
  result.ypos = ypos + other.ypos;
  return result;
}

real Point2::wedgeProduct(Point2 other) {
  return xpos*other.ypos - ypos*other.xpos;
}

real Point2::dot(Point2 other) {
  return xpos*other.xpos + ypos*other.ypos;
}

void Point2::scale(real scalar) {
  xpos *= scalar;
  ypos *= scalar;
}

bool Point2::operator<(const Point2& other) const {
  return xpos < other.xpos || (xpos == other.xpos && ypos < other.ypos);
}

void Point2::debug() {
  cout << "(" << xpos << "," << ypos << ")" << endl;
}

void Point2::setXpos(real param) {
  xpos = param;
}

void Point2::setYpos(real param) {
  ypos = param;
}
