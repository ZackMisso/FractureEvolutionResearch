#include "vertex.h"
#include "../test/debugController.h"
#include <GL/glut.h>

Vertex::Vertex(real x,real y) {
  edges = new Array<Edge*>();
  faceIDs = new Array<Integer>();
  //edgeIDs = new Array<int>();
  location.xpos = x;
  location.ypos = y;
  id = -1;
  selected = false;
  boundary = false;
}

Vertex::Vertex(Point2 point) {
  edges = new Array<Edge*>();
  faceIDs = new Array<Integer>();
  //edgeIDs = new Array<int>();
  location.xpos = point.xpos;
  location.ypos = point.ypos;
  id = -1;
  selected = false;
  boundary = false;
}

Vertex::~Vertex() {
  while(edges->getSize())
    edges->removeLast();
  //while(edgeIDs->getSize())
  //  edgeIDs->removeLast();
  delete edges;
  //delete edgeIDs;
}

Vertex* Vertex::copy(Array<Edge*>* newEdges) {
  Vertex* newVert = new Vertex(location);
  newVert->setID(id);
  newVert->setSelected(selected);
  newVert->setBoundary(boundary);
  for(int i=0;i<edges->getSize();i++) {
    int idd = edges->get(i)->getID();
    Edge* edge = 0x0;
    for(int j=0;j<newEdges->getSize();j++)
      if(idd == newEdges->get(j)->getID()) {
        edge = newEdges->get(j);
        j = newEdges->getSize();
      }
    newVert->getEdges()->add(edge);
    //newVert->getEdgeIDs()->add(idd);
  }
  for(int i=0;i<faceIDs->getSize();i++)
    newVert->getFaceIDs()->add(faceIDs->get(i));
  return newVert;
}

void Vertex::draw() {
	glVertex2f(location.xpos,location.ypos);
}

void Vertex::updateEdges() {
  for(int i=0;i<edges->getSize();i++) {
    Edge* edge = edges->get(i);
    if(edge->getFirstVertID() == id)
      edge->setFirst(location);
    if(edge->getSecondVertID() == id)
      edge->setSecond(location);
  }
}

void Vertex::updateFaceIDs() {
  faceIDs->clear();
  for(int i=0;i<edges->getSize();i++) {
    Edge* edge = edges->get(i);
    for(int j=0;j<edge->getFaceIDs()->getSize();j++) {
      bool toAdd = true;
      for(int k=0;k<faceIDs->getSize();k++)
        if(faceIDs->get(k).val == edge->getFaceIDs()->get(j).val)
          toAdd = false;
      if(toAdd)
        faceIDs->add(edge->getFaceIDs()->get(j));
    }
  }
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
Array<Integer>* Vertex::getFaceIDs() { return faceIDs; }
//Array<int>* Vertex::getEdgeIDs() { return edgeIDs; }
Point2 Vertex::getLocation() { return location; }
int Vertex::getID() { return id; }
bool Vertex::getSelected() { return selected; }
bool Vertex::getBoundary() { return boundary; }

void Vertex::setEdges(Array<Edge*>* param) { edges = param; }
void Vertex::setFaceIDs(Array<Integer>* param) { faceIDs = param ;}
//void Vertex::setEdgeIDs(Array<int>* param) { edgeIDs = param; }
void Vertex::setLocation(Point2 param) { location = param; }
void Vertex::setID(int param) { id = param; }
void Vertex::setSelected(bool param) { selected = param; }
void Vertex::setBoundary(bool param) { boundary = param; }
