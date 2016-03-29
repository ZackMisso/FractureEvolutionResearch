#include "vertPositionMutation.h"
#include "../../misc/rng.h"

VertPositionMutation::VertPositionMutation() { }

VertPositionMutation::VertPositionMutation(real param) : MutationFunction(param) { }

VertPositionMutation::~VertPositionMutation() { }

Individual* VertPositionMutation::mutate(Individual* individual) {
  Fracture* copy = individual->getFracture()->copy();
  Individual* newIndividual = new Individual(mutate(copy));
  return newIndividual;
}

Fracture* VertPositionMutation::mutate(Fracture* fracture) {
  // get all verts that are not boundaries
  Array<Vertex*>* nonBoundary = new Array<Vertex*>();
  for(int i=0;i<fracture->getVerts()->getSize();i++)
    if(!fracture->getVerts()->get(i)->getBoundary())
      nonBoundary->add(fracture->getVerts()->get(i));
  int numVerts = nonBoundary->getSize();
  if(!numVerts)
    return fracture;
  // get a random non-boundary vert
  int randVert = RNG::RandomInt(numVerts);
  Vertex* ranVert = nonBoundary->get(randVert);
  // get the face surrounding the point
  Array<Face*>* facesWithVert = fracture->getFacesWithVertex(ranVert);
  Face* faceToMutateAround = new Face();
  for(int i=0;i<facesWithVert->getSize();i++) {
    Face* tmp = facesWithVert->get(i);
    for(int j=0;j<tmp->getVerts()->getSize();j++)
      if(tmp->getVerts()->get(j)->getID() != ranVert->getID())
        faceToMutateAround->getVerts()->add(tmp->getVerts()->get(j));
    for(int j=0;j<tmp->getEdges()->getSize();j++)
      if(!tmp->getEdges()->get(j)->eitherMatch(ranVert->getID()))
        faceToMutateAround->getEdges()->add(tmp->getEdges()->get(j));
  }
  // detect if the face is convex or not
  faceToMutateAround->detectIfConvex();
  if(faceToMutateAround->getIsConvex()) {
    // convex case mutation
  } else {
    // concave case mutation
  }
  return fracture;
}
