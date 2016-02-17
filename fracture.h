#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "array.h"
#include "vertex.h"
#include "edge.h"

class Fracture {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges; // will have multiple references
  Array<Face*>* faces;
public:
  Fracture();
  ~Fracture();
	void createNewVertex(float x,float y);
	void createNewEdge(Vertex* one,Vertex* two);
	void draw();
  // getter methods
  Array<Face*>* getFaces();
  Array<Edge*>* getEdges();
  Array<Vertex*>* getVerts();
};

#endif
