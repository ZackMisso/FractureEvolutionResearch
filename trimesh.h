#ifndef __TRIMESH_H__
#define __TRIMESH_H__

#include "array.h"
#include "tri.h"

class TriMesh {
private:
  Array<Tri*>* triangles;
public:
  TriMesh();
  ~TriMesh();
  void addTriangles(Array<Tri*>* moreTriangles);
  void addBoundaryTriangles();
  void calculateAllAdjacents();
  void clean();
  void draw();
  // getter methods
  Array<Tri*>* getTriangles();
  // setter methods
  void setTriangles(Array<Tri*>* param);
};

#endif
