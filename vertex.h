#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "array.h"
#include "edge.h"
#include "point2.h"

class Vertex {
private:
  Array<Edge*> *edges;
  Point2 location; // [0.0-1.0 , 0.0-1.0]
public:
  Vertex(float x,float y);
  Vertex(Point2 point);
  ~Vertex();
};

#endif
