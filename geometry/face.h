#ifndef __FACE_H__
#define __FACE_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "../dataStructures/integer.h"
#include "../misc/idTracker.h"
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
  real cross(const Point2& o,const Point2& a,const Point2& b);
public:
  Face();
  Face(Array<Vertex*>* verts);
  ~Face();
  Face* copy(Array<Vertex*>* newVerts,Array<Edge*>* newEdges);
  bool contains(real x,real y);
  bool contains(Point2 point);
  bool contains(Vertex* vert);
  bool contains(Edge* edge);
  Array<Face*>* separate(Vertex* newVert,IDTracker* ids);
  Array<Point2>* getConvexHull();
  Array<Face*>* separate(real x,real y);
  Array<Point2>* sortPointsByPath();
  Array<Integer>* sortVertIDsByPath();
  Array<Point2>* reversePath(Array<Point2>* sortedPath);
  Array<Vertex*>* getVertsInEdge(Edge* edge);
  bool isClockwise(Array<Point2>* sortedPath);
  void detectIfConvex();
  void splitIntoTrimesh();
  void splitIntoTrimeshConvex();
  void splitIntoTrimeshConcave();
  void findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc);
  Array<Vertex*>* findVertsOnPath(Array<Edge*>* edges);
  void draw();
  real area();
  void addVert(Vertex* vert);
  void addEdge(Edge* edge);
  void clear();
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
