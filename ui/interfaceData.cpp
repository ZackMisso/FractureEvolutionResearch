#include "interfaceData.h"

InterfaceData::InterfaceData() {
  //currentFracture = 0x0;
  selectedEdge = 0x0;
  selectedVertOne = 0x0;
  selectedVertTwo = 0x0;
  mouseX = 0.0f;
  mouseY = 0.0f;
  selectingFaces = false;
  selectingEdges = false;
  selectingVerts = false;
}

InterfaceData::~InterfaceData() {
  // All current variables are destroyed elsewhere
}

void InterfaceData::draw() {
  // implement if needed
}

//Fracture* InterfaceData::getCurrentFracture() { return currentFracture; }
Face* InterfaceData::getSelectedFace() { return selectedFace; }
Edge* InterfaceData::getSelectedEdge() { return selectedEdge; }
Vertex* InterfaceData::getSelectedVertOne() { return selectedVertOne; }
Vertex* InterfaceData::getSelectedVertTwo() { return selectedVertTwo; }
real InterfaceData::getMouseX() { return mouseX; }
real InterfaceData::getMouseY() { return mouseY; }
bool InterfaceData::getSelectingFaces() { return selectingFaces; }
bool InterfaceData::getSelectingEdges() { return selectingEdges; }
bool InterfaceData::getSelectingVerts() { return selectingVerts; }

//void InterfaceData::setCurrentFracture(Fracture* param) { currentFracture = param; }
void InterfaceData::setSelectedFace(Face* param) { selectedFace = param; }
void InterfaceData::setSelectedEdge(Edge* param) { selectedEdge = param; }
void InterfaceData::setSelectedVertOne(Vertex* param) { selectedVertOne = param; }
void InterfaceData::setSelectedVertTwo(Vertex* param) { selectedVertTwo = param; }
void InterfaceData::setMouseX(real param) { mouseX = param; }
void InterfaceData::setMouseY(real param) { mouseY = param; }
void InterfaceData::setSelectingFaces(bool param) { selectingFaces = param; }
void InterfaceData::setSelectingEdges(bool param) { selectingEdges = param; }
void InterfaceData::setSelectingVerts(bool param) { selectingVerts = param; }
