#ifndef __EDGE3_H__
#define __EDGE3_H__

#include "../globalInclude.h"
#include "point3.h"

class Edge3 {
private:
  Point3 first;
  Point3 second;
public:
  Edge3();
  Edge3(Point3 one,Point3 two);
  Edge3(real x,real y,real z,real xx,real yy,real zz);
  // getter methods
  Point3 getFirst();
  Point3 getSecond();
  // setter methods
  void setFirst(Point3 param);
  void setSecond(Point3 param);
};

#endif
