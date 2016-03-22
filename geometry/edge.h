#ifndef __EDGE_H__
#define __EDGE_H__

#include "../globalInclude.h"
#include "point2.h"
#include "../dataStructures/array.h"

class Edge {
private:
  Point2 first;
  Point2 second;
  int id;
  bool selected;
public:
  Edge(Point2 one,Point2 two);
  Edge(real x,real y,real xx,real yy);
  void draw();
  bool intersects(Edge* other);
  Edge* intersects(Array<Edge*>* edges,Edge* ignore);
  bool eitherMatch(Point2 point);
  Point2 getIntersectionPoint(Edge* other);
  Point2 getOtherPoint(Point2 point);
  Point2 getPointBetween(real pos);
  void split(Array<Edge*>* cb,Point2 point);
  real determinant(Edge* other);
  //bool isOn(Edge* other);
	// getters
  Point2 getFirst();
  Point2 getSecond();
  int getID();
  bool getSelected();
  // setters
  void setFirst(Point2 point);
  void setSecond(Point2 point);
  void setID(int param);
  void setSelected(bool param);
};

#endif
