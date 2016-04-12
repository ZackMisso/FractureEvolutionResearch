#include "renderSettings.h"

RenderSettings::RenderSettings() {
  displayVerts = true;
  displayEdges = true;
  displayFaces = false;
  displayFaceTrimesh = false;
  vertSize = 10;
  edgeSize = 3;
  triangulationOne = false;
  triangulationTwo = false;
  vertAddConvexOne = false;
  vertAddConvexTwo = false;
  vertAddConvexThree = false;
  vertAddConcaveOne = false;
  vertAddConcaveTwo = false;
  vertAddConcaveThree = false;
  vertAddConcaveFour = false;
  vertAddConcaveFive = false;
  vertMoveConvexOne = false;
  vertMoveConvexTwo = false;
  vertMoveConcaveOne = false;
  vertAddConcaveTwo = false;
}

RenderSettings::~RenderSettings() { }

void RenderSettings::resetDisplay() {
  triangulationOne = false;
  triangulationTwo = false;
  vertAddConvexOne = false;
  vertAddConvexTwo = false;
  vertAddConvexThree = false;
  vertAddConcaveOne = false;
  vertAddConcaveTwo = false;
  vertAddConcaveThree = false;
  vertAddConcaveFour = false;
  vertAddConcaveFive = false;
  vertMoveConvexOne = false;
  vertMoveConvexTwo = false;
  vertMoveConcaveOne = false;
  vertAddConcaveTwo = false;
}

//InterfaceData* RenderSettings::getInterfaceRef() { return interfaceRef; }
int RenderSettings::getVertSize() { return vertSize; }
int RenderSettings::getEdgeSize() { return edgeSize; }
bool RenderSettings::getDisplayVerts() { return displayVerts; }
bool RenderSettings::getDisplayEdges() { return displayEdges; }
bool RenderSettings::getDisplayFaces() { return displayFaces; }
bool RenderSettings::getDisplayFaceTrimesh() { return displayFaceTrimesh; }
bool RenderSettings::getTriangulationOne() { return triangulationOne; }
bool RenderSettings::getTriangulationTwo() { return triangulationTwo; }
bool RenderSettings::getVertAddConvexOne() { return vertAddConvexOne; }
bool RenderSettings::getVertAddConvexTwo() { return vertAddConvexTwo; }
bool RenderSettings::getVertAddConvexThree() { return vertAddConvexThree; }
bool RenderSettings::getVertAddConcaveOne() { return vertAddConcaveOne; }
bool RenderSettings::getVertAddConcaveTwo() { return vertAddConcaveTwo; }
bool RenderSettings::getVertAddConcaveThree() { return vertAddConcaveThree; }
bool RenderSettings::getVertAddConcaveFour() { return vertAddConcaveFour; }
bool RenderSettings::getVertAddConcaveFive() { return vertAddConcaveFive; }
bool RenderSettings::getVertMoveConvexOne() { return vertMoveConvexOne; }
bool RenderSettings::getVertMoveConvexTwo() { return vertMoveConvexTwo; }
bool RenderSettings::getVertMoveConcaveOne() { return vertMoveConcaveOne; }
bool RenderSettings::getVertMoveConcaveTwo() { return vertMoveConcaveTwo; }

//void RenderSettings::setInterfaceRef(InterfaceData* param) { interfaceRef = param; }
void RenderSettings::setVertSize(int param) { vertSize = param; }
void RenderSettings::setEdgeSize(int param) { edgeSize = param; }
void RenderSettings::setDisplayVerts(bool param) { displayVerts = param; }
void RenderSettings::setDisplayEdges(bool param) { displayEdges = param; }
void RenderSettings::setDisplayFaces(bool param) { displayFaces = param; }
void RenderSettings::setDisplayFaceTrimesh(bool param) { displayFaceTrimesh = param; }
void RenderSettings::setTriangulationOne(bool param) { triangulationOne = param; }
void RenderSettings::setTriangulationTwo(bool param) { triangulationTwo = param; }
void RenderSettings::setVertAddConvexOne(bool param) { vertAddConvexOne = param; }
void RenderSettings::setVertAddConvexTwo(bool param) { vertAddConvexTwo = param; }
void RenderSettings::setVertAddConvexThree(bool param) { vertAddConvexThree = param; }
void RenderSettings::setVertAddConcaveOne(bool param) { vertAddConcaveOne = param; }
void RenderSettings::setVertAddConcaveTwo(bool param) { vertAddConcaveTwo = param; }
void RenderSettings::setVertAddConcaveThree(bool param) { vertAddConcaveThree = param; }
void RenderSettings::setVertAddConcaveFour(bool param) { vertAddConcaveFour = param; }
void RenderSettings::setVertAddConcaveFive(bool param) { vertAddConcaveFive = param; }
void RenderSettings::setVertMoveConvexOne(bool param) { vertMoveConvexOne = param; }
void RenderSettings::setVertMoveConvexTwo(bool param) { vertMoveConvexTwo = param; }
void RenderSettings::setVertMoveConcaveOne(bool param) { vertMoveConcaveOne = param; }
void RenderSettings::setVertMoveConcaveTwo(bool param) { vertMoveConcaveTwo = param; }
