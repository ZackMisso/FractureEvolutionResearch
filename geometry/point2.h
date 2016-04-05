#ifndef __POINT2_H__
#define __POINT2_H__

#include "../globalInclude.h"

// TODO :: Replace all of these methods with operators

class Point2 {
public:
  real xpos;
  real ypos;
  Point2();
  Point2(real x,real y);
  bool equals(Point2 other);
  Point2 minus(Point2 other);
  Point2 add(Point2 other);
  real wedgeProduct(Point2 other);
  real dot(Point2 other);
  void scale(real scaler);
  // debug
  void debug();
  // setter methods
  void setXpos(real param);
  void setYpos(real param);
};

#endif
