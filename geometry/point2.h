#ifndef __POINT2_H__
#define __POINT2_H__

#include "../globalInclude.h"

class Point2 {
public:
  real xpos;
  real ypos;
  Point2();
  Point2(real x,real y);
  bool equals(Point2 other);
  float wedgeProduct(Point2 other);
  float dot(Point2 other);
  // debug
  void debug();
  // setter methods
  void setXpos(real param);
  void setYpos(real param);
};

#endif
