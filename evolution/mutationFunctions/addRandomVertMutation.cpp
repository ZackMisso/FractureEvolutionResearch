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
    cout << "Face Contents: ";
    cout << endl;
    //DebugController::writeFaceContentsState(faceToMutate);
    // split and choose trimesh
    DebugController::writeFaceContentsState(faceToMutate);
    faceToMutate->splitIntoTrimeshConcave();
    int numTris = faceToMutate->getTriMesh()->getSize();
    cout << "Num Tris: " << numTris << endl;
    int randTri = RNG::RandomInt(numTris);
    Tri* tri = faceToMutate->getTriMesh()->get(randTri);
    cout << "Chosen Tri:" << endl;
    tri->debug();
    // create barys
    float barys[2];
    real baryTotal = 0.0;
    for(int i=0;i<2;i++) {
      barys[i] = RNG::RandomFloat();
      baryTotal += barys[i];
    }
    // normalize barys
    for(int i=0;i<2;i++)
      barys[i] /= baryTotal;
    // calculate new point based on barys
    real newVertX = 0.0;
    real newVertY = 0.0;
    cout << "first bary: " << barys[0] << endl;
    cout << "second bary: " << barys[1] << endl;
    //cout << "third bary: " << barys[2] << endl;
    //cout << "bary Total: " << barys[0] + barys[1] + barys[2] << endl;
    cout << "bary Total: " << barys[0] + barys[1] << endl;
    newVertX = tri->getPointOne().xpos;
    newVertX += barys[0] * (tri->getPointTwo().xpos - tri->getPointOne().xpos);
    newVertX += barys[1] * (tri->getPointThree().xpos - tri->getPointOne().xpos);
    newVertY = tri->getPointOne().ypos;
    newVertY += barys[0] * (tri->getPointTwo().ypos - tri->getPointOne().ypos);
    newVertY += barys[1] * (tri->getPointThree().ypos - tri->getPointOne().ypos);
    //newVertX += tri->getPointOne().xpos * barys[0];
    //newVertX += tri->getPointTwo().xpos * barys[1];
    //newVertX += tri->getPointThree().xpos * barys[2];
    //newVertY += tri->getPointOne().ypos * barys[0];
    //newVertY += tri->getPointTwo().ypos * barys[1];
    //newVertY += tri->getPointThree().ypos * barys[2];
    cout << "New Vert: " << newVertX << " " << newVertY << endl;
    Vertex* newVert = fracture->giveVertexID(new Vertex(newVertX,newVertY));
    // now split
    cout << "Beginning Split" << endl;
    Array<Face*>* newFaces = faceToMutate->separate(newVert,fracture->getIDs());
    cout << "Finished Split" << endl;
    cout << "Number of New Faces: " << newFaces->getSize() << endl;
    if(newFaces) {
      cout << "Removing Old Face" << endl;
      fracture->getFaces()->remove(faceToMutate);
      cout << "Adding New Faces" << endl;
      for(int i=0;i<newFaces->getSize();i++) {
        cout << "Adding Face" << endl;
        fracture->getFaces()->add(newFaces->get(i));
        cout << "Added Face" << endl;
      }
      cout << "Finished Adding new Faces" << endl;
    }
  }
  cout << "Returning Fracture" << endl;
  return fracture;
}
