#include "box.h"

Box::Box() {
  origin.xpos = 0.0f;
  origin.ypos = 0.0f;
  width = 0.0f;
  height = 0.0f;
}

Box::Box(Point2 point,float w,float h) {
  origin.xpos = point.xpos;
  origin.ypos = point.ypos;
  width = w;
  height = h;
}

Box::Box(float x,float y,float w,float h) {
  origin.xpos = x;
  origin.ypos = y;
  width = w;
  height = h;
}

Point2 Box::getOrigin() { return origin; }
float Box::getWidth() { return width; }
float Box::getHeignt() { return height; }

void Box::setOrigin(Point2 point) { origin = point; }
void Box::setWidth(float param) { width = param; }
void Box::setHeight(float param) { height = param; }
