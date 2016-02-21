#include "mutations.h"
#include "rng.h"

void Mutations::AddRandomVertex(Fracture* fracture) {
  float randX = RNG::RandomFloat(-0.5f,0.5f);
  float randY = RNG::RandomFloat(-0.5f,0.5f);

  Array<Face*>* faces = fracture->getFaces();
  Face* oldFace = 0x0;

  for(int i=0;i<faces->getSize();i++)
    if(faces->get(i)->contains(randX,randY))
      oldFace = faces->get(i);

  if(!oldFace) { // could possibly cause problems
    AddRandomVertex(fracture);
    return;
  }

  Array<Face*>* newFaces = oldFace->separate(randX,randY);

  if(newFaces) {
    for(int i=0;i<newFaces->getSize();i++)
      faces->add(newFaces->get(i));

    faces->remove(oldFace);
    while(newFaces->getSize())
      newFaces->removeLast();
    delete oldFace;
    delete newFaces;
  }
}

void Mutations::RemoveRandomEdge(Fracture* fracture) {
  // to be implemented
}

void Mutations::BoxCrossOver(Fracture* one,Fracture* other) {
  // to be implemented
}
