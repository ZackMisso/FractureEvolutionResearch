#ifndef __FACE3_H__
#define __FACE3_H__

#include "globalInclude.h"
#include "array.h"
#include "edge3.h"
#include "vertex3.h"

class Face3 {
private:
  Array<Edge3*>* edges;
  Array<Vertex3*>* verts;
public:
  Face3();
  ~Face3();
  // getter methods
  Array<Edge3*>* getEdges();
  Array<Vertex3*>* getVerts();
  // setter methods
  void setEdges(Array<Edge3*>* param);
  void setVerts(Array<Vertex3*>* param);
};

#endif
