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

void Debug::printLines(Array<Edge*>* edges) {
  cout << "/////////// PRINTING LINES /////////////" << endl;
  for(int i=0;i<edges->getSize();i++) {
    cout << "X :: " << edges->get(i)->getFirst().xpos << " Y :: " << edges->get(i)->getFirst().ypos << endl;
    cout << "X :: " << edges->get(i)->getSecond().xpos << " Y :: " << edges->get(i)->getSecond().ypos << endl;
    cout << endl;
  }
  cout << "/////////////////////////////////////////" << endl;
}
