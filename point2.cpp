#include "point2.h"

#include <iostream>
using namespace std;

Point2::Point2() {
  xpos = 0.0f;
  ypos = 0.0f;
}

Point2::Point2(float x,float y) {
  xpos = x;
  ypos = y;
}

bool Point2::equals(Point2 other) {
  return xpos == other.xpos && ypos == other.ypos;
}

float Point2::wedgeProduct(Point2 other) {
  return xpos*other.ypos - ypos*other.xpos;
}

float Point2::dot(Point2 other) {
  return xpos*other.xpos + ypos*other.ypos;
}

void Point2::debug() {
  cout << "(" << xpos << "," << ypos << ")" << endl;
}

void Point2::setXpos(float param) {
  xpos = param;
}

void Point2::setYpos(float param) {
  ypos = param;
}
