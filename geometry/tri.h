#ifndef __TRI_H__
#define __TRI_H__

#include "../globalInclude.h"
#include "point2.h"
#include "edge.h"

class Tri {
private:
  Point2 points[3];
  int pointIDs[3];
  Edge** edges;
  //Tri** adjacents;
  //bool isBoundary; // sort of hack
public:
  // constructors
  Tri();
  Tri(Point2 one,Point2 two,Point2 three);
  Tri(Edge* one,Edge* two,Edge* three);
  Tri(Tri* one,Tri* two,Tri* trhee);
  Tri(Edge* edge,Point2 point,int pointID);
  ~Tri();
  // other methods
  //void findAdjacents(Array<Tri*>* triangles); // implement later
  real area();
  bool equals(Tri* other);
  void updatePosition(int id,Point2 newPos);
  Point2 interpolatePosition(real baryOne,real baryTwo,real baryThree);
  bool isInside(Point2 point);
  bool isInsideOld(Point2 point);
  real sign(Point2 one,Point2 two,Point2 three);
  void debug();
  void draw();
  // getter methods
  Point2 getPoint(int num);
  Point2 getPointOne();
  Point2 getPointTwo();
  Point2 getPointThree();
  int getPointIDOne();
  int getPointIDTwo();
  int getPointIDThree();
  Edge* getEdge(int num);
  Edge* getEdgeOne();
  Edge* getEdgeTwo();
  Edge* getEdgeThree();
  //Tri* getAdjacent(int num);
  //Tri* getAdjacentOne();
  //Tri* getAdjacentTwo();
  //Tri* getAdjacentThree();
  //bool getIsBoundary();
  // setter methods
  void setPoint(int num,Point2 param);
  void setPointOne(Point2 param);
  void setPointTwo(Point2 param);
  void setPointThree(Point2 param);
  void setPointIDOne(int param);
  void setPointIDTwo(int param);
  void setPointIDThree(int param);
  void setEdge(int num,Edge* param);
  void setEdgeOne(Edge* param);
  void setEdgeTwo(Edge* param);
  void setEdgeThree(Edge* param);
  //void setAdjacent(int num,Tri* param);
  //void setAdjacentOne(Tri* param);
  //void setAdjacentTwo(Tri* param);
  //void setAdjacentThree(Tri* param);
  //void setIsBoundary(bool param);
};

#endif
