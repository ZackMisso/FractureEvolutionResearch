#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "array.h"
#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "renderSettings.h"

class Fracture {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges; // will have multiple references
  Array<Face*>* faces;
public:
  Fracture();
  ~Fracture();
  void init(int points);
  void clearAndReloadFaces();
	void createNewVertex(float x,float y);
	void createNewEdge(Vertex* one,Vertex* two);
  void recount();
  //void debug();
  Array<Face*>* getFacesWithVertex(Vertex* vert);
  Array<Face*>* getFacesWithEdge(Edge* edge);
	void draw(RenderSettings* renderSettings);
  // getter methods
  Array<Face*>* getFaces();
  Array<Edge*>* getEdges();
  Array<Vertex*>* getVerts();
};

#endif
