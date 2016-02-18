#include "vertex.h"
#include <GL/glut.h>

Vertex::Vertex(float x,float y) {
  edges = new Array<Edge*>();
  location.xpos = x;
  location.ypos = y;
  selected = false;
}

Vertex::Vertex(Point2 point) {
  location.xpos = point.xpos;
  location.ypos = point.ypos;
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

void Vertex::setEdges(Array<Edge*>* param) { edges = param; }
void Vertex::setLocation(Point2 param) { location = param; }
