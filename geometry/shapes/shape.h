#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "../../globalInclude.h"
#include "../../dataStructures/array.h"
#include "../vertex.h"
#include "../edge.h"
#include "../box.h"
#include "../fracture.h"

class Shape {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges;
  Box* boundingBox;
public:
  Shape();
  ~Shape();
  virtual void createShape();
  void calculateBoundingBox();
  Fracture* applyFracture(Fracture* fracture);
  // getter methods
  Array<Vertex*>* getVerts();
  Array<Edge*>* getEdges();
  Box* getBoundingBox();
  // setter methods
  void setVerts(Array<Vertex*>* param);
  void setEdges(Array<Edge*>* param);
  void setBoundingBox(Box* param);
}

#endif
