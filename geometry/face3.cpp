#include "face3.h"

Face3::Face3() {
  edges = new Array<Edge3*>();
  verts = new Array<Vertex3*>();
}

Face3::~Face3() {
  // to be implemented
}

Array<Edge3*>* Face3::getEdges() { return edges; }
Array<Vertex3*>* Face3::getVerts() { return verts; }

void Face3::setEdges(Array<Edge3*>* param) { edges = param; }
void Face3::setVerts(Array<Vertex3*>* param) { verts = param; }
