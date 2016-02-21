#include "mutations.h"
#include "rng.h"

#include <iostream>

using namespace std;

void Mutations::AddRandomVertex(Fracture* fracture) {
  cout << "Creating Random Position" << endl;
  float randX = RNG::RandomFloat(-0.5f,0.5f);
  float randY = RNG::RandomFloat(-0.5f,0.5f);
  cout << "Position :: " << randX << " :: " << randY << endl;
  Array<Face*>* faces = fracture->getFaces();
  Face* oldFace = 0x0;
  cout << "Running Contains Method" << endl;
  for(int i=0;i<faces->getSize();i++)
    if(faces->get(i)->contains(randX,randY))
      oldFace = faces->get(i);

  if(!oldFace) { // could possibly cause problems
    cout << "THERE WAS AN ERROR.... Or a Strike of Bad Luck" << endl;
    //AddRandomVertex(fracture);
    return;
  }
  cout << "Found Face" << endl;
  cout << "Separating the Face" << endl;
  Array<Face*>* newFaces = oldFace->separate(randX,randY);
  cout << "Finished Separations" << endl;
  if(newFaces) {
    for(int i=0;i<newFaces->getSize();i++)
      faces->add(newFaces->get(i));
    cout << "Doing Final Removals" << endl;
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
