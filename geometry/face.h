#ifndef __FACE_H__
#define __FACE_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "edge.h"
#include "vertex.h"
#include "point2.h"
#include "box.h"
#include "tri.h"

class Face {
private:
  Array<Tri*>* triMesh;
  Array<Vertex*>* verts;
  Array<Edge*>* edges;
  int id;
  bool isConvex;
  bool selected;
  void clearTrimesh();
public:
  Face();
  Face(Array<Vertex*>* verts);
  ~Face();
  bool contains(real x,real y);
  bool contains(Point2 point);
  bool contains(Vertex* vert);
  bool contains(Edge* edge);
  Array<Face*>* separate(Vertex* newVert);
  Array<Point2>* getConvexHull();
  //Array<Face*>* separate(Point2 newPoint);
  //Array<Face*>* separate(Point2 start,Point2 end);
  Array<Face*>* separate(real x,real y);
  Array<Point2>* sortPointsByPath();
  Array<Point2>* reversePath(Array<Point2>* sortedPath);
  bool isClockwise(Array<Point2>* sortedPath);
  void detectIfConvex();
  void splitIntoTrimesh();
  void splitIntoTrimeshConvex();
  void splitIntoTrimeshConcave();
  void findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc);
  Array<Vertex*>* findVertsOnPath(Array<Edge*>* edges);
  // getter methods
  Array<Tri*>* getTriMesh();
  Array<Vertex*>* getVerts();
  Array<Edge*>* getEdges();
  int getID();
  bool getSelected();
  bool getIsConvex();
  // setter methods
  void setTriMesh(Array<Tri*>* param);
  void setVerts(Array<Vertex*>* param);
  void setEdges(Array<Edge*>* param);
  void setID(int param);
  void setSelected(bool param);
  void setIsConvex(bool param);
};

#endif
