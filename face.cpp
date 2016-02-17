#include "face.h"

Face::Face() {
  verts = new Array<Vertex*>();
  edges = new Array<Vertex*>();
}

Face::Face(Array<Vertex*>* verts) {
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  // initialize arrays
}

Face::~Face() {
  while(verts->getSize())
    verts->removeLast();
  while(edges->getSize())
    edges->removeLast();
  delete verts;
  delete edges;
}

// this must work for polygons of any size
bool Face::contains(Point2 point) {
  int intersections = 0;
  // create horizontal ray
  Edge *ray = new Edge(-1.0f,point.ypos,point.xpos,point.ypos);
  // get the number of intersections
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->intersects(ray))
      intersections++;
  // if odd this face contains the point
  delete ray;
  return intersections % 2;
}

// this may also need different forms of implementations
Array<Face*>* Face::separate(Point2 newPoint) {
  // to be implemented
  return 0x0;
}

Array<Vertex*>* Face::getVerts() { return verts; }
Array<Edge*>* Face::getEdges() { return edges; }

void Face::setVerts(Array<Vertex*>* param) { verts = param; }
void Face::setEdges(Array<Edge*>* param) { edges = param; }