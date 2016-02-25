#include "debugController.h"

#include <iostream>

using namespace std;

int DebugController::nextVertNum = 0;
int DebugController::nextEdgeNum = 0;
int DebugController::nextFaceNum = 0;

void DebugController::init() {
  nextVertNum = 0;
  nextFaceNum = 0;
  nextEdgeNum = 0;
}

int DebugController::getNextVert() {
  return nextVertNum++;
}

int DebugController::getNextEdge() {
  return nextEdgeNum++;
}

int DebugController::getNextFace() {
  return nextFaceNum++;
}

void DebugController::writeDebugState(Fracture* fracture) {
  writeSingleStates(fracture);
  cout << endl;
  writeRelationalStates(fracture);
}

void DebugController::writeEdgeState(Edge* edge) {
  cout << "Edge :: " << edge->getID();
  cout << " :: (" << edge->getFirst().xpos;
  cout << "," << edge->getFirst().ypos << ")->(";
  cout << edge->getSecond().xpos << ",";
  cout << edge->getSecond().ypos << ")" << endl;
}

void DebugController::writeVertState(Vertex* vert) {
  cout << "Vert :: " << vert->getID();
  cout << " :: (" << vert->getLocation().xpos;
  cout << "," << vert->getLocation().ypos;
  cout << ")" << endl;
}

void DebugController::writeFaceState(Face* face) {
  cout << "Face :: " << face->getID() << endl;
}

void DebugController::writeSingleStates(Fracture* fracture) {
  cout << endl;
  for(int i=0;i<fracture->getVerts()->getSize();i++)
    writeVertState(fracture->getVerts()->get(i));
  cout << endl;
  for(int i=0;i<fracture->getEdges()->getSize();i++)
    writeEdgeState(fracture->getEdges()->get(i));
  cout << endl;
  for(int i=0;i<fracture->getFaces()->getSize();i++)
    writeFaceState(fracture->getFaces()->get(i));
  cout << endl;
}

void DebugController::writeRelationalStates(Fracture* fracture) {
  for(int i=0;i<fracture->getVerts()->getSize();i++) {
    Vertex* vert = fracture->getVerts()->get(i);
    cout << "Vert :: " << vert->getID();
    for(int j=0;j<vert->getEdges()->getSize();j++)
      cout << " :: " << vert->getEdges()->get(j)->getID();
    cout << " End" << endl;
  }
  for(int i=0;i<fracture->getEdges()->getSize();i++) {
    Edge* edge = fracture->getEdges()->get(i);
    cout << "Edge :: " << edge->getID();
    for(int j=0;j<fracture->getVerts()->getSize();j++)
      if(fracture->getVerts()->get(j)->isMatch(edge->getFirst()))
        cout << " :: First: " << fracture->getVerts()->get(j)->getID();
    for(int j=0;j<fracture->getVerts()->getSize();j++)
      if(fracture->getVerts()->get(j)->isMatch(edge->getSecond()))
        cout << " :: Second: " << fracture->getVerts()->get(j)->getID();
    cout << endl;
  }
  for(int i=0;i<fracture->getFaces()->getSize();i++) {
    Face* face = fracture->getFaces()->get(i);
    cout << endl;
    cout << "Face :: " << face->getID() << endl;
    cout << "Edges :: ";
    for(int j=0;j<face->getEdges()->getSize();j++)
      cout << face->getEdges()->get(j)->getID() << "; ";
    cout << endl;
    cout << "Verts :: ";
    for(int j=0;j<face->getVerts()->getSize();j++)
      cout << face->getVerts()->get(j)->getID() << "; ";
    cout << endl;
  }
}
