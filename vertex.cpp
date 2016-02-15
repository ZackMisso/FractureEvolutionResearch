#include "vertex.h"

Vertex::Vertex(float x,float y) {
  edges = new Array<Edge*>();
  location.xpos = x;
  location.ypos = y;
}

Vertex::Vertex(Point2 point) {
  location.xpos = point.xpos;
  location.ypos = point.ypos;
}

Vertex::~Vertex() {
  while(edges->getSize())
    edges->removeLast();
  delete edges;
}
