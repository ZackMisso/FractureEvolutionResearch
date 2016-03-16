#include "trimesh.h"

TriMesh::TriMesh() {
  triangles = new Array<Tri*>();
}

TriMesh::~TriMesh() {
  while(triangles->getSize())
    delete triangles->removeLast();
  delete triangles;
}

void TriMesh::clean() {
  while(triangles->getSize())
    triangles->removeLast();
}

void TriMesh::addTriangles(Array<Tri*>* moreTriangles) {
  for(int i=0;i<moreTriangles->getSize();i++)
    triangles->add(moreTriangles->get(i));
}

void TriMesh::addBoundaryTriangles() {
  Point2 tl(-0.5,0.5);
  Point2 tr(0.5,0.5);
  Point2 bl(-0.5,-0.5);
  Point2 br(0.5,-0.5);
  Point2 n(0.0,1.0);
  Point2 s(0.0,-1.0);
  Point2 e(1.0,0.0);
  Point2 w(-1.0,0.0);
  triangles->add(new Tri(tl,bl,w));
  triangles->add(new Tri(tl,tr,n));
  triangles->add(new Tri(bl,br,s));
  triangles->add(new Tri(tr,br,e));
}

void TriMesh::draw() {
  for(int i=0;i<triangles->getSize();i++)
    triangles->get(i)->draw();
}

// THIS IS SLOW.... NEEDS OPTIMIZATIONS
void TriMesh::calculateAllAdjacents() {
  // to be implemented
}

Array<Tri*>* TriMesh::getTriangles() { return triangles; }

void TriMesh::setTriangles(Array<Tri*>* param) { triangles = param; }
