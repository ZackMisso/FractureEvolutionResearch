#ifndef __FACE_H__
#define __FACE_H__

#include "array.h"
#include "edge.h"
#include "vertex.h"
#include "point2.h"
#include "box.h"

class Face {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges;
public:
  Face();
  Face(Array<Vertex*>* verts);
  ~Face();
  bool contains(float x,float y);
  bool contains(Point2 point);
  bool contains(Vertex* vert);
  bool contains(Edge* edge);
  Array<Face*>* separate(Vertex* newVert);
  Array<Face*>* separate(Point2 newPoint);
  void findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc);
  Array<Vertex*>* findVertsOnPath(Array<Edge*>* edges);
  // getter methods
  Array<Vertex*>* getVerts();
  Array<Edge*>* getEdges();
  // setter methods
  void setVerts(Array<Vertex*>* param);
  void setEdges(Array<Edge*>* param);
};

#endif
