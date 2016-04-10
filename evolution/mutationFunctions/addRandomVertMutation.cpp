#include "addRandomVertMutation.h"
#include "../../misc/rng.h"
#include "../../test/debugController.h"
#include <iostream>

using namespace std;

AddRandomVertMutation::AddRandomVertMutation() { }

AddRandomVertMutation::AddRandomVertMutation(real param) : MutationFunction(param) { }

AddRandomVertMutation::~AddRandomVertMutation() { }

Individual* AddRandomVertMutation::mutate(Individual* individual) {
  cout << "Starting Add Vert Mutation" << endl;
  Fracture* copy = individual->getFracture()->copy();
  cout << "Mutating" << endl;
  Individual* newIndividual = new Individual(mutate(copy));
  return newIndividual;
}

// TODO :: clean up allocations
Fracture* AddRandomVertMutation::mutate(Fracture* fracture) {
  cout << "Random Vert Mutation" << endl;
  int randFace = RNG::RandomInt(fracture->getFaces()->getSize());
  Face* faceToMutate = fracture->getFaces()->get(randFace);
  faceToMutate->detectIfConvex();
  if(faceToMutate->getIsConvex()) {
    // convex case mutation
    cout << "Is Convex" << endl;
    int numPoints = faceToMutate->getVerts()->getSize();
    float barys[numPoints];
    real baryTotal = 0.0;
    // create barys
    for(int i=0;i<numPoints;i++) {
      barys[i] = RNG::RandomFloat();
      baryTotal += barys[i];
    }
    // normalize barys
    for(int i=0;i<numPoints;i++)
      barys[i] /= baryTotal;
    // calculate new point based on barys
    real newVertX = 0.0;
    real newVertY = 0.0;
    for(int i=0;i<numPoints;i++) {
      newVertX += barys[i] * faceToMutate->getVerts()->get(i)->getLocation().xpos;
      newVertY += barys[i] * faceToMutate->getVerts()->get(i)->getLocation().ypos;
    }
    Vertex* newVert = fracture->giveVertexID(new Vertex(newVertX,newVertY));
    // now split
    Array<Face*>* newFaces = faceToMutate->separate(newVert,fracture->getIDs());
    if(newFaces) {
      fracture->getFaces()->remove(faceToMutate);
      for(int i=0;i<newFaces->getSize();i++)
        fracture->getFaces()->add(newFaces->get(i));
    }
  } else {
    // concave case mutation
    cout << "Is Concave" << endl;
    // split and choose trimesh
    faceToMutate->splitIntoTrimeshConcave();
    int numTris = faceToMutate->getTriMesh()->getSize();
    int randTri = RNG::RandomInt(numTris);
    Tri* tri = faceToMutate->getTriMesh()->get(randTri);
    // create barys
    float barys[3];
    real baryTotal = 0.0;
    for(int i=0;i<3;i++) {
      barys[i] = RNG::RandomFloatMinMax(0.1,0.9);
      baryTotal += barys[i];
    }
    // normalize barys (third bary is not really needed)
    for(int i=0;i<2;i++)
      barys[i] /= baryTotal;
    // calculate new point based on barys
    real newVertX = 0.0;
    real newVertY = 0.0;
    newVertX = tri->getPointOne().xpos;
    newVertX += barys[0] * (tri->getPointTwo().xpos - tri->getPointOne().xpos);
    newVertX += barys[1] * (tri->getPointThree().xpos - tri->getPointOne().xpos);
    newVertY = tri->getPointOne().ypos;
    newVertY += barys[0] * (tri->getPointTwo().ypos - tri->getPointOne().ypos);
    newVertY += barys[1] * (tri->getPointThree().ypos - tri->getPointOne().ypos);
    Vertex* newVert = fracture->giveVertexID(new Vertex(newVertX,newVertY));
    // now split
    cout << "Beginning Split" << endl;
    Array<Face*>* newFaces = faceToMutate->separate(newVert,fracture->getIDs());
    cout << "Finished Split" << endl;
    if(newFaces) {
      fracture->getFaces()->remove(faceToMutate);
      for(int i=0;i<newFaces->getSize();i++)
        fracture->getFaces()->add(newFaces->get(i));
    }
  }
  fracture->recount();
  return fracture;
}
