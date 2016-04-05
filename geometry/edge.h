#ifndef __EDGE_H__
#define __EDGE_H__

#include "../globalInclude.h"
#include "point2.h"
#include "../misc/idTracker.h"
#include "../dataStructures/array.h"
#include "../dataStructures/integer.h"

class Edge {
private:
  Array<Integer>* faceIDs;
  Point2 first;
  Point2 second;
  int id;
  int firstVertID;
  int secondVertID;
  bool selected;
  bool isBoundary;
public:
  Edge(Point2 one,Point2 two);
  Edge(Point2 one,Point2 two,int idone,int idtwo);
  Edge(real x,real y,real xx,real yy);
  Edge(real x,real y,real xx,real yy,int idone,int idtwo);
  Edge* copy();
  void draw();
  bool intersects(Edge* other);
  bool intersects(Edge* other,Point2* ut);
  bool intersectsOld(Edge* other);
  Edge* intersects(Array<Edge*>* edges,Edge* ignore);
  bool eitherMatch(Point2 point);
  bool eitherMatch(int pointID);
  Point2 getIntersectionPoint(Edge* other);
  Point2 getOtherPoint(Point2 point);
  Point2 getOtherPoint(int pointID);
  Point2 getPointBetween(real pos);
  void splitOld(Array<Edge*>* cb,Point2 point);
  void split(Array<Edge*>* cb,Point2 point,int pointID,IDTracker* ids);
  real determinant(Edge* other);
  real length();
  //bool isOn(Edge* other);
	// getters
  Array<Integer>* getFaceIDs();
  Point2 getFirst();
  Point2 getSecond();
  int getID();
  int getFirstVertID();
  int getSecondVertID();
  bool getSelected();
  bool getIsBoundary();
  // setters
  void setFaceIDs(Array<Integer>* param);
  void setFirst(Point2 point);
  void setSecond(Point2 point);
  void setID(int param);
  void setFirstVertID(int param);
  void setSecondVertID(int param);
  void setSelected(bool param);
  void setIsBoundary(bool param);
};

#endif
