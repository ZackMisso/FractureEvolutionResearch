#include "debug.h"
#include <iostream>

using namespace std;

void Debug::printPoints(Array<Vertex*>* verts) {
  cout << "/////////// PRINTING POINTS /////////////" << endl;
  for(int i=0;i<verts->getSize();i++) {
    cout << "X :: " << verts->get(i)->getLocation().xpos << " Y :: " << verts->get(i)->getLocation().ypos << endl;
    cout << endl;
  }
  cout << "/////////////////////////////////////////" << endl;
}

void Debug::printPoint(Point2 point) {
  cout << "//////////// PRINTING POINT /////////////" << endl;
  cout << "X :: " << point.xpos << " Y :: " << point.ypos << endl;
  cout << "/////////////////////////////////////////" << endl;
}

void Debug::printLines(Array<Edge*>* edges) {
  cout << "/////////// PRINTING LINES /////////////" << endl;
  for(int i=0;i<edges->getSize();i++) {
    cout << "X :: " << edges->get(i)->getFirst().xpos << " Y :: " << edges->get(i)->getFirst().ypos << endl;
    cout << "X :: " << edges->get(i)->getSecond().xpos << " Y :: " << edges->get(i)->getSecond().ypos << endl;
    cout << endl;
  }
  cout << "/////////////////////////////////////////" << endl;
}

void Debug::printFracture(Fracture* fracture) {
  cout << "////////// PRINTING FRACTURE ////////////" << endl;
  cout << endl;
  for(int i=0;i<fracture->getFaces()->getSize();i++) {
    cout << "FACE :: " << i << endl;
    cout << endl;
    printLines(fracture->getFaces()->get(i)->getEdges());
    cout << endl;
    printPoints(fracture->getFaces()->get(i)->getVerts());
    cout << endl;
  }
  cout << "/////////////////////////////////////////" << endl;
}

void Debug::printLine(Edge* edge) {
  cout << edge->getFirst().xpos << " " << edge->getFirst().ypos << " " << edge->getSecond().xpos << " " << edge->getSecond().ypos << endl;
}
