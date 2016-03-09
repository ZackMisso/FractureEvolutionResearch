#include "mutations.h"
#include "rng.h"
#include "debug.h"
#include "debugController.h"

#include <iostream>

using namespace std;

void Mutations::AddRandomVertex(Fracture* fracture) {
  float randX = RNG::RandomFloat(-0.5f,0.5f);
  float randY = RNG::RandomFloat(-0.5f,0.5f);
  DebugController::writeCreateSeparationPoint(randX,randY);
  Array<Face*>* faces = fracture->getFaces();
  Face* oldFace = 0x0;
  for(int i=0;i<faces->getSize();i++)
    if(faces->get(i)->contains(randX,randY))
      oldFace = faces->get(i);

  if(!oldFace) { // could possibly cause problems
    cout << "THERE WAS AN ERROR.... Or a Strike of Bad Luck" << endl;
    return;
  }

  Array<Face*>* newFaces = oldFace->separate(randX,randY);

  if(newFaces) {
    for(int i=0;i<newFaces->getSize();i++)
      faces->add(newFaces->get(i));
    DebugController::writeDeleteFace(oldFace);
    faces->remove(oldFace);
    while(newFaces->getSize())
      newFaces->removeLast();
    delete oldFace;
    delete newFaces;
    fracture->recount();
  }
}

void Mutations::RemoveRandomEdge(Fracture* fracture) {
  // to be implemented
}

void Mutations::BoxCrossOver(Fracture* one,Fracture* other) {
  // to be implemented
}
