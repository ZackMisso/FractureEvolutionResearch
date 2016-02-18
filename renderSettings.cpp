#include "renderSettings.h"

RenderSettings::RenderSettings() {
  displayVerts = true;
  displayEdges = true;
  displayFaces = false;
  vertSize = 10;
  edgeSize = 3;
}

RenderSettings::~RenderSettings() { }

int RenderSettings::getVertSize() { return vertSize; }
int RenderSettings::getEdgeSize() { return edgeSize; }
bool RenderSettings::getDisplayVerts() { return displayVerts; }
bool RenderSettings::getDisplayEdges() { return displayEdges; }
bool RenderSettings::getDisplayFaces() { return displayFaces; }

void RenderSettings::setVertSize(int param) { vertSize = param; }
void RenderSettings::setEdgeSize(int param) { edgeSize = param; }
void RenderSettings::setDisplayVerts(bool param) { displayVerts = param; }
void RenderSettings::setDisplayEdges(bool param) { displayEdges = param; }
void RenderSettings::setDisplayFaces(bool param) { displayFaces = param; }
