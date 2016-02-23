#ifndef __EDGE3_H__
#define __EDGE3_H__

#include "point3.h"

class Edge3 {
private:
  Point3 first;
  Point3 second;
public:
  Edge3();
  Edge3(Point3 one,Point3 two);
  Edge3(float x,float y,float z,float xx,float yy,float zz);
  // getter methods
  Point3 getFirst();
  Point3 getSecond();
  // setter methods
  void setFirst(Point3 param);
  void setSecond(Point3 param);
};

#endif
