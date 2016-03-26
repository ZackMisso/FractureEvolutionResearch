#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "trimesh.h"
#include "../settings/renderSettings.h"
//#include "interfaceData.h"

class Fracture {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges; // will have multiple references
  Array<Face*>* faces;
  TriMesh* triMesh;
  int nextVertID;
  int nextEdgeID;
  int nextFaceID;
public:
  Fracture();
  ~Fracture();
  void init(int points);
  void clearAndReloadFaces();
	void createNewVertex(real x,real y);
	void createNewEdge(Vertex* one,Vertex* two);
  void createTriMesh();
  Vertex* giveVertexID(Vertex* vert);
  Edge* giveEdgeID(Edge* edge);
  Face* giveFaceID(Face* face);
  bool doesSimilarEdgeExists(Edge* edge);
  void recount();
  //void debug();
  Array<Face*>* getFacesWithVertex(Vertex* vert);
  Array<Face*>* getFacesWithEdge(Edge* edge);
	void draw(RenderSettings* renderSettings,InterfaceData* interfaceData);
  Array<Face*>* calculateAllFaces();
  // getter methods
  Array<Face*>* getFaces();
  Array<Edge*>* getEdges();
  Array<Vertex*>* getVerts();
  TriMesh* getTriMesh();
  int getNextVertID();
  int getNextEdgeID();
  int getNextFaceID();
  // setter methods
  void setFaces(Array<Face*>* param);
  void setEdges(Array<Edge*>* param);
  void setVerts(Array<Vertex*>* param);
  void setNextVertID(int param);
  void setNextEdgeID(int param);
  void setNextFaceID(int param);
};

#endif
