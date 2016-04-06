#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "trimesh.h"
#include "../settings/renderSettings.h"
#include "../misc/idTracker.h"
//#include "interfaceData.h"

class Fracture {
private:
  Array<Vertex*>* verts;
  Array<Edge*>* edges; // will have multiple references
  Array<Face*>* faces;
  TriMesh* triMesh;
  IDTracker* ids;
public:
  Fracture();
  Fracture(bool param);
  ~Fracture();
  Fracture* copy();
  void init(int points);
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
  // getter methods
  Array<Face*>* getFaces();
  Array<Edge*>* getEdges();
  Array<Vertex*>* getVerts();
  TriMesh* getTriMesh();
  IDTracker* getIDs();
  // setter methods
  void setFaces(Array<Face*>* param);
  void setEdges(Array<Edge*>* param);
  void setVerts(Array<Vertex*>* param);
  void setIDs(IDTracker* param);
};

#endif
