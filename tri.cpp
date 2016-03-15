#include "tri.h"

Tri::Tri() {
  // to be implemented
  edges = new Edge()[3];
  // adjacents must be created outside of this class
}

Tri::Tri(Point2 one,Point2 two,Point2 three) {
  // to be implemented
}

Tri::Tri(Edge* one,Edge* two,Edge* three) {
  // to be implemented
}

Tri::Tri(Tri* one,Tri* two,Tri* trhee) {
  // to be implemented
}

Tri::~Tri() {
  delete edges[2];
  delete edges[1];
  delete edges[0];
  delete adjacents[2];
  delete adjacents[1];
  delete adjacents[0];
}

void findAdjacents(Array<Tri*>* triangles) {
  // to be implemented
}

Point2 getPointOne() { return points[0]; }
Point2 getPointTwo() { return points[1]; }
Point2 getPointThree() { return points[2]; }
Edge* getEdgeOne() { return edges[0]; }
Edge* getEdgeTwo() { return edges[1]; }
Edge* getEdgeThree() { return edges[2]; }
Tri* getAdjacentOne() { return adjacents[0]; }
Tri* getAdjacentTwo() { return adjacents[1]; }
Tri* getAdjacentThree() { return adjacents[2]; }

void setPointOne(Point2 param) { points[0] = param; }
void setPointTwo(Point2 param) { points[1] = param; }
void setPointThree(Point2 param) { points[2] = param; }
void setEdgeOne(Edge* param) { edges[0] = param; }
void setEdgeTwo(Edge* param) { edges[1] = param; }
void setEdgeThree(Edge* param) { edges[2] = param; }
void setAdjacentOne(Tri* param) { adjacents[0] = param; }
void setAdjacentTwo(Tri* param) { adjacents[1] = param; }
void setAdjacentThree(Tri* param) { adjacents[2] = param; }
