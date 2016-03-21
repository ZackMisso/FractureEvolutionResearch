#ifndef __INTERFACEDATA_H__
#define __INTERFACEDATA_H__

//#include "fracture.h"
#include "globalInclude.h"
#include "face.h"
#include "edge.h"
#include "vertex.h"

class InterfaceData {
private:
  //Fracture* currentFracture; // I dont think this is needed
  Face* selectedFace;
  Edge* selectedEdge;
  Vertex* selectedVertOne;
  Vertex* selectedVertTwo;
  real mouseX;
  real mouseY;
  bool selectingFaces;
  bool selectingEdges;
  bool selectingVerts;
public:
  InterfaceData();
  ~InterfaceData();
  void draw();
  // getter methods
  //Fracture* getCurrentFracture();
  Face* getSelectedFace();
  Edge* getSelectedEdge();
  Vertex* getSelectedVertOne();
  Vertex* getSelectedVertTwo();
  real getMouseX();
  real getMouseY();
  bool getSelectingFaces();
  bool getSelectingEdges();
  bool getSelectingVerts();
  // setter methods
  //void setCurrentFracture(Fracture* param);
  void setSelectedFace(Face* param);
  void setSelectedEdge(Edge* param);
  void setSelectedVertOne(Vertex* param);
  void setSelectedVertTwo(Vertex* param);
  void setMouseX(real param);
  void setMouseY(real param);
  void setSelectingFaces(bool param);
  void setSelectingEdges(bool param);
  void setSelectingVerts(bool param);
};

#endif
