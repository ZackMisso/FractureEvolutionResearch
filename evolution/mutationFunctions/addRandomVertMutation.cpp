#include "addRandomVertMutation.h"
#include "../../misc/rng.h"

AddRandomVertMutation::AddRandomVertMutation() { }

AddRandomVertMutation::AddRandomVertMutation(real param) : MutationFunction(param) { }

AddRandomVertMutation::~AddRandomVertMutation() { }

Individual* AddRandomVertMutation::mutate(Individual* individual) {
  Individual* newIndividual = new Individual(mutate(individual->getFracture()));
  return newIndividual;
}

Fracture* AddRandomVertMutation::mutate(Fracture* fracture) {
  int randFace = RNG::RandomInt(fracture->getFaces()->getSize());
  Face* faceToMutate = fracture->getFaces()->get(randFace);
  faceToMutate->detectIfConvex();
  if(faceToMutate->getIsConvex()) {
    // convex case ,utation
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
    faceToMutate->separate(newVert);
  } else {
    // concave case mutation
    // split and choose trimesh
    faceToMutate->splitIntoTrimeshConcave();
    int numTris = faceToMutate->getTriMesh()->getSize();
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
    faceToMutate->separate(newVert);
  }
  return fracture;
}
