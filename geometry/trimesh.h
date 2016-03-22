#ifndef __TRIMESH_H__
#define __TRIMESH_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "tri.h"
#include "face.h"
#include "../ui/interfaceData.h"

class TriMesh {
private:
  Array<Tri*>* triangles;
  Face* face;
public:
  TriMesh();
  ~TriMesh();
  void addTriangles(Array<Tri*>* moreTriangles);
  //void addBoundaryTriangles();
  //void calculateAllAdjacents();
  void clean();
  void debug();
  void draw(InterfaceData* interfaceData);
  // getter methods
  Array<Tri*>* getTriangles();
  Face* getFace();
  // setter methods
  void setTriangles(Array<Tri*>* param);
  void setFace(Face* param);
};

#endif
