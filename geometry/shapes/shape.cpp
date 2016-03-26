#include "shape.h"

Shape::Shape() {
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  boundingBox = new Box();
}

Shape::~Shape() {
  while(verts->getSize())
    delete verts->removeLast();
  while(edges->getSize())
    delete edges->removeLast();
  delete verts;
  delete edges;
  delete box;
}

void Shape::createShape() {
  // create a rectangle for a bracelet
  Vertex* tr = new Vertex();
  Vertex* tl = new Vertex();
  Vertex* br = new Vertex();
  Vertex* bl = new Vertex();
  Edge* left = new Edge();
  Edge* right = new Edge();
  Edge* top = new Edge();
  Edge* bottom = new Edge();
  verts->add(tr);
  verts->add(tl);
  verts->add(bl);
  verts->add(br);
  edges->add(left);
  edges->add(right);
  edges->add(top);
  edges->add(bottom);
}

void Shape::calculateBoundingBox() {
  if(!verts->getSize()) {
    boundingBox = 0x0;
    return;
  }
  real minX = verts->get(0)->getLocation().xpos;
  real minY = verts->get(0)->getLocation().ypos;
  real maxX = verts->get(0)->getLocation().xpos;
  real maxY = verts->get(0)->getLocation().ypos;
  for(int i=1;i<verts->getSize();i++) {
    if(verts->get(i)->getLocation().xpos < minX)
      minX = verts->get(i)->getLocation().xpos;
    if(verts->get(i)->getLocation().ypos < minY)
      minY = verts->get(i)->getLocation().ypos;
    if(verts->get(i)->getLocation().xpos > maxX)
      maxX = verts->get(i)->getLocation().xpos;
    if(verts->get(i)->getLocation().ypos > maxY)
      maxY = verts->get(i)->getLocation().ypos;
  }
  if(boundingBox)
    delete boundingBox;
  box = new Box(minX,maxY,maxX-minX,maxY-minY);
}

Fracture* Shape::applyFracture(Fracture* fracture) {
  // to be implemented
  // this will be a doosey
  return fracture;
}

Array<Vertex*>* Shape::getVerts() { return verts; }
Array<Edge*>* Shape::getEdges() { return edges; }
Box* Shape::getBoundingBox() { return boundingBox; }

void Shape::setVerts(Array<Vertex*>* param) { verts = param; }
void Shape::setEdge(Array<Edge*>* param) { edges = param; }
void Shape::setBoundingBox(Box* param) { boundingBox = param; }
