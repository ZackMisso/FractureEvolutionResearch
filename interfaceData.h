#ifndef __INTERFACEDATA_H__
#define __INTERFACEDATA_H__

#include "fracture.h"

class InterfaceData {
private:
  Fracture* currentFracture;
  Face* selectedFace;
  Edge* selectedEdge;
  Vertex* selectedVertOne;
  Vertex* selectedVertTwo;
  float mouseX;
  float mouseY;
  bool selectingFaces;
  bool selectingEdges;
  bool selectingVerts;
public:
  InterfaceData();
  ~InterfaceData();
  void draw();
  // getter methods
  Fracture* getCurrentFracture();
  Face* getSelectedFace();
  Edge* getSelectedEdge();
  Vertex* getSelectedVertOne();
  Vertex* getSelectedVertTwo();
  float getMouseX();
  float getMouseY();
  bool getSelectingFaces();
  bool getSelectingEdges();
  bool getSelectingVerts();
  // setter methods
  void setCurrentFracture(Fracture* param);
  void setSelectedFace(Face* param);
  void setSelectedEdge(Edge* param);
  void setSelectedVertOne(Vertex* param);
  void setSelectedVertTwo(Vertex* param);
  void setMouseX(float param);
  void setMouseY(float param);
  void setSelectingFaces(bool param);
  void setSelectingEdges(bool param);
  void setSelectingVerts(bool param);
};

#endif
