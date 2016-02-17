#ifndef __BOX_H__
#define __BOX_H__

#include "point2.h"

class Box {
private:
  Point2 origin; // top left
  float width;
  float height;
public:
  Box();
  Box(Point2 point,float w,float h);
  Box(float x,float y,float w,float h);
  // getter methods
  Point2 getOrigin();
  float getWidth();
  float getHeignt();
  // setter methods
  void setOrigin(Point2 point);
  void setWidth(float param);
  void setHeight(float param);
};

#endif
