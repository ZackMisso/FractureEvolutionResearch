#ifndef __TRI_H__
#define __TRI_H__

#include "point2.h"
#include "edge.h"

class Tri {
private:
  Point2 points[3];
  Edge* edges;
  Tri* adjacents;
public:
  Tri();
  Tri(Point2 one,Point2 two,Point2 three);
  Tri(Edge* one,Edge* two,Edge* three);
  Tri(Tri* one,Tri* two,Tri* trhee);
  ~Tri();
  // getter methods
  Point2 getPointOne();
  Point2 getPointTwo();
  Point2 getPointThree();
  Edge* getEdgeOne();
  Edge* getEdgeTwo();
  Edge* getEdgeThree();
  Tri* getAdjacentOne();
  Tri* getAdjacentTwo();
  Tri* getAdjacentThree();
  // setter methods
  void setPointOne(Point2 param);
  void setPointTwo(Point2 param);
  void setPointThree(Point2 param);
  void setEdgeOne(Edge* param);
  void setEdgeTwo(Edge* param);
  void setEdgeThree(Edge* param);
  void setAdjacentOne(Tri* param);
  void setAdjacentTwo(Tri* param);
  void setAdjacentThree(Tri* param);
};

#endif
