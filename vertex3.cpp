#include "vertex3.h"
#include "debugController.h"

Vertex3::Vertex3(float x,float y,float z) {
  edges = new Array<Edge3*>();
  location.xpos = x;
  location.ypos = y;
  location.zpos = z;
  id = DebugController::getNextVert();
  selected = false;
}

Vertex3::Vertex3(Point3 point) {
  edges = new Array<Edge3*>();
  location.xpos = point.xpos;
  location.ypos = point.ypos;
  location.zpos = point.zpos;
  id = DebugController::getNextVert();
  selected = false;
}

Vertex3::~Vertex3() {
  // to be implemented
}

Array<Edge3*>* Vertex3::getEdges() { return edges; }
Point3 Vertex3::getLocation() { return location; }
int Vertex3::getID() { return id; }
bool Vertex3::getSelected() { return selected; }

void Vertex3::setEdges(Array<Edge3*>* param) { edges = param; }
void Vertex3::setLocation(Point3 param) { location = param; }
void Vertex3::setID(int param) { id = param; }
void Vertex3::setSelected(bool param) { selected = param; }
