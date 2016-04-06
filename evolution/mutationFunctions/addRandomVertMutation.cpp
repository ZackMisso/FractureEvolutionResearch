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
  cout << "In Mutate" << endl;
  int randFace = RNG::RandomInt(fracture->getFaces()->getSize());
  Face* faceToMutate = fracture->getFaces()->get(randFace);
  cout << "Detecting if Convex" << endl;
  faceToMutate->detectIfConvex();
  if(faceToMutate->getIsConvex()) {
    // convex case mutation
    cout << "Is Convex" << endl;
    int numPoints = faceToMutate->getVerts()->getSize();
    float barys[numPoints];
    real baryTotal = 0.0;
    // create barys
    cout << "Creating Barys" << endl;
    for(int i=0;i<numPoints;i++) {
      barys[i] = RNG::RandomFloat();
      baryTotal += barys[i];
    }
    cout << "Normalizing Barys" << endl;
    // normalize barys
    for(int i=0;i<numPoints;i++)
      barys[i] /= baryTotal;
    // calculate new point based on barys
    real newVertX = 0.0;
    real newVertY = 0.0;
    cout << "Getting New Point" << endl;
    for(int i=0;i<numPoints;i++) {
      newVertX += barys[i] * faceToMutate->getVerts()->get(i)->getLocation().xpos;
      newVertY += barys[i] * faceToMutate->getVerts()->get(i)->getLocation().ypos;
    }
    cout << "Creating new Vert" << endl;
    Vertex* newVert = fracture->giveVertexID(new Vertex(newVertX,newVertY));
    // now split
    cout << "Calling Separate" << endl;
    Array<Face*>* newFaces = faceToMutate->separate(newVert,fracture->getIDs());
    cout << "Left Separate" << endl;
    //cout << "Number of New Faces: " << newFaces->getSize() << endl;
    if(newFaces) {
      cout << "Number of New Faces: " << newFaces->getSize() << endl;
      fracture->getFaces()->remove(faceToMutate);
      cout << "Removed Old Face" << endl;
      for(int i=0;i<newFaces->getSize();i++) {
        cout << "Adding Face: " << i << endl;
        cout << "Number of Edges: " << newFaces->get(i)->getEdges()->getSize() << endl;
        for(int j=0;j<newFaces->get(i)->getEdges()->getSize();j++) {
          //cout << "Before Face" << endl;
          Face* face = newFaces->get(i);
          //cout << "Before Array" << endl;
          Array<Edge*>* edgs = face->getEdges();
          //cout << "Before Edge" << endl;
          Edge* ed = edgs->get(j);
          //cout << "Before DebugController" << endl;
          DebugController::writeEdgeState(ed);
          //cout << "WHATTTTT" << endl;
        }
        cout << "Number of Verts: " << newFaces->get(i)->getVerts()->getSize() << endl;
        for(int j=0;j<newFaces->get(i)->getVerts()->getSize();j++)
          DebugController::writeVertState(newFaces->get(i)->getVerts()->get(j));
        fracture->getFaces()->add(newFaces->get(i));
      }
      cout << "Added New Faces" << endl;
    }
  } else {
    // concave case mutation
    cout << "Is Concave" << endl;
    // split and choose trimesh
    faceToMutate->splitIntoTrimeshConcave();
    int numTris = faceToMutate->getTriMesh()->getSize();
    cout << "Num Tris: " << numTris << endl;
    int randTri = RNG::RandomInt(numTris);
    Tri* tri = faceToMutate->getTriMesh()->get(randTri);
    // create barys
    float barys[3];
    real baryTotal = 0.0;
    for(int i=0;i<3;i++) {
      barys[i] = RNG::RandomFloat();
      baryTotal += barys[i];
    }
    // normalize barys
    for(int i=0;i<3;i++)
      barys[i] /= baryTotal;
    // calculate new point based on barys
    real newVertX = 0.0;
    real newVertY = 0.0;
    newVertX += tri->getPointOne().xpos * barys[0];
    newVertX += tri->getPointTwo().xpos * barys[1];
    newVertX += tri->getPointThree().xpos * barys[2];
    newVertY += tri->getPointOne().xpos * barys[0];
    newVertY += tri->getPointTwo().xpos * barys[1];
    newVertY += tri->getPointThree().xpos * barys[2];
    Vertex* newVert = fracture->giveVertexID(new Vertex(newVertX,newVertY));
    // now split
    Array<Face*>* newFaces = faceToMutate->separate(newVert,fracture->getIDs());
    if(newFaces) {
      fracture->getFaces()->remove(faceToMutate);
      for(int i=0;newFaces->getSize();i++)
        fracture->getFaces()->add(newFaces->get(i));
    }
  }
  cout << "Returning Fracture" << endl;
  return fracture;
}
