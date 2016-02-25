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
  int id;
  bool selected;
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
  Array<Face*>* separate(Point2 start,Point2 end);
  Array<Face*>* separate(float x,float y);
  void findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc);
  Array<Vertex*>* findVertsOnPath(Array<Edge*>* edges);
  // getter methods
  Array<Vertex*>* getVerts();
  Array<Edge*>* getEdges();
  int getID();
  bool getSelected();
  // setter methods
  void setVerts(Array<Vertex*>* param);
  void setEdges(Array<Edge*>* param);
  void setID(int param);
  void setSelected(bool param);
};

#endif
