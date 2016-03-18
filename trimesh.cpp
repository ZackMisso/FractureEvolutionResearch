#include "trimesh.h"
#include <GL/glut.h>

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
  Tri* one = new Tri(tl,bl,w);
  Tri* two = new Tri(tl,tr,n);
  Tri* three = new Tri(bl,br,s);
  Tri* four = new Tri(tr,br,e);
  one->setIsBoundary(true);
  two->setIsBoundary(true);
  three->setIsBoundary(true);
  four->setIsBoundary(true);
  triangles->add(one);
  triangles->add(two);
  triangles->add(three);
  triangles->add(four);
}

void TriMesh::draw(InterfaceData* data) {
  if(face==data->getSelectedFace())
    glColor3f(.3f,.3f,.3f);
  for(int i=0;i<triangles->getSize();i++)
    triangles->get(i)->draw();
  glColor3f(0.0f,0.0f,1.0f);
}

// THIS IS SLOW.... NEEDS OPTIMIZATIONS
// NEEDS HEAVY OPTIMIZATIONS
void TriMesh::calculateAllAdjacents() { // NEED TO TEST
  for(int i=0;i<triangles->getSize();i++) {
    Tri* current = triangles->get(i);
    // Adjacents for boundaries dont need to be known...
    if(!current->getIsBoundary()) {
      for(int j=0;j<3;j++) {
        for(int k=0;k<triangles->getSize();k++) {
          if(k!=i) {
            Tri* toTest = triangles->get(k);
            for(int l=0;l<3;l++) {
              if(toTest->getEdge(l)->isOn(current->getEdge(j))) {
                current->setAdjacent(j,toTest);
                l=4;
                k=triangles->getSize();
              }
            }
          }
        }
      }
    }
  }
}

Array<Tri*>* TriMesh::getTriangles() { return triangles; }
Face* TriMesh::getFace() { return face; }

void TriMesh::setTriangles(Array<Tri*>* param) { triangles = param; }
void TriMesh::setFace(Face* param) { face = param; }
