#ifndef __EDGE_H__
#define __EDGE_H__

#include "point2.h"

class Edge {
private:
  Point2 first;
  Point2 second;
  bool selected;
public:
  Edge(Point2 one,Point2 two);
  Edge(float x,float y,float xx,float yy);
  void draw();
  bool intersects(Edge* other);
  Point2 getOtherPoint(Point2 point);
	// getters
  Point2 getFirst();
  Point2 getSecond();
  // setters
  void setFirst(Point2 point);
  void setSecond(Point2 point);
};

#endif
