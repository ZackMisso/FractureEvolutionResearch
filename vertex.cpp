#include "vertex.h"
#include <GL/glut.h>
#include "debugController.h"

Vertex::Vertex(float x,float y) {
  edges = new Array<Edge*>();
  location.xpos = x;
  location.ypos = y;
  id = DebugController::getNextVert();
  selected = false;
}

Vertex::Vertex(Point2 point) {
  edges = new Array<Edge*>();
  location.xpos = point.xpos;
  location.ypos = point.ypos;
  id = DebugController::getNextVert();
  selected = false;
}

Vertex::~Vertex() {
  while(edges->getSize())
    edges->removeLast();
  delete edges;
}

void Vertex::draw() {
	glVertex2f(location.xpos,location.ypos);
}

bool Vertex::isMatch(Point2 point) {
  return point.xpos == location.xpos && point.ypos == location.ypos;
}

bool Vertex::isConnected(Vertex* other) {
  for(int i=0;i<edges->getSize();i++) {
    Point2 p;
    if(isMatch(edges->get(i)->getFirst()))
      p = edges->get(i)->getSecond();
    else
      p = edges->get(i)->getFirst();
    if(other->isMatch(p))
      return true;
  }
  return false;
}

Array<Edge*>* Vertex::getEdges() { return edges; }
Point2 Vertex::getLocation() { return location; }
int Vertex::getID() { return id; }
bool Vertex::getSelected() { return selected; }

void Vertex::setEdges(Array<Edge*>* param) { edges = param; }
void Vertex::setLocation(Point2 param) { location = param; }
void Vertex::setID(int param) { id = param; }
void Vertex::setSelected(bool param) { selected = param; }
