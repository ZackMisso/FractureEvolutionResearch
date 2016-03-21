#include "box.h"

Box::Box() {
  origin.xpos = 0.0f;
  origin.ypos = 0.0f;
  width = 0.0f;
  height = 0.0f;
}

Box::Box(Point2 point,real w,real h) {
  origin.xpos = point.xpos;
  origin.ypos = point.ypos;
  width = w;
  height = h;
}

Box::Box(real x,real y,real w,real h) {
  origin.xpos = x;
  origin.ypos = y;
  width = w;
  height = h;
}

Point2 Box::getOrigin() { return origin; }
real Box::getWidth() { return width; }
real Box::getHeignt() { return height; }

void Box::setOrigin(Point2 point) { origin = point; }
void Box::setWidth(real param) { width = param; }
void Box::setHeight(real param) { height = param; }
