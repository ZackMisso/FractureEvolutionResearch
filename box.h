#ifndef __BOX_H__
#define __BOX_H__

#include "globalInclude.h"
#include "point2.h"

class Box {
private:
  Point2 origin; // top left
  real width;
  real height;
public:
  Box();
  Box(Point2 point,real w,real h);
  Box(real x,real y,real w,real h);
  // getter methods
  Point2 getOrigin();
  real getWidth();
  real getHeignt();
  // setter methods
  void setOrigin(Point2 point);
  void setWidth(real param);
  void setHeight(real param);
};

#endif
