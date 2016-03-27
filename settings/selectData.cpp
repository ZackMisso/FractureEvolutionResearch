#include "selectData.h"

SelectData::SelectData() {
  selectedVert = 0x0;
  selectedEdge = 0x0;
  selectedFace = 0x0;
}

SelectData::~SelectData() {
  // does nothing
}

Vertex* SelectData::getSelectedVert() { return selectedVert; }
Edge* SelectData::getSelectedEdge() { return selectedEdge; }
Face* SelectData::getSelectedFace() { return selectedFace; }

void SelectData::setSelectedVert(Vertex* param) { selectedVert = param; }
void SelectData::setSelectedEdge(Edge* param) { selectedEdge = param; }
void SelectData::setSelectedFace(Face* param) { selectedFace = param; }
