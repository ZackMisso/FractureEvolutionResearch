#ifndef __POINT2_H__
#define __POINT2_H__

class Point2 {
public:
  float xpos;
  float ypos;
  Point2();
  Point2(float x,float y);
  bool equals(Point2 other);
  float wedgeProduct(Point2 other);
  // setter methods
  void setXpos(float param);
  void setYpos(float param);
};

#endif
