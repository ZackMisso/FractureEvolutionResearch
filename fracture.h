#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "array.h"
#include "vertex.h"
#include "edge.h"

class Fracture {
private:
  Array<Vertex*> *verts;
  Array<Edge*> *edges; // will have multiple references
public:
  Fracture();
  ~Fracture();
	void createNewVertex(float x,float y);
	void createNewEdge(Vertex* one,Vertex* two);
	void draw();
};

#endif
