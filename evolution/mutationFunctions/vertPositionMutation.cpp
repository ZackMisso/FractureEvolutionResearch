#include "vertPositionMutation.h"
#include "../../misc/rng.h"
#include "../../settings/evolutionSettings.h"
#include "../../dataStructures/integer.h"

VertPositionMutation::VertPositionMutation() { }

VertPositionMutation::VertPositionMutation(real param) : MutationFunction(param) { }

VertPositionMutation::~VertPositionMutation() { }

Individual* VertPositionMutation::mutate(Individual* individual) {
  Fracture* copy = individual->getFracture()->copy();
  Individual* newIndividual = new Individual(mutate(copy));
  return newIndividual;
}

Fracture* VertPositionMutation::mutate(Fracture* fracture) {
  // get all verts that are not corners
  Array<Vertex*>* nonCorner = new Array<Vertex*>();
  for(int i=0;i<fracture->getVerts()->getSize();i++)
    if(!fracture->getVerts()->get(i)->getIsCorner())
      nonCorner->add(fracture->getVerts()->get(i));
  int numVerts = nonCorner->getSize();
  if(!numVerts) // if only corners return the original fracture
    return fracture;
  // get a random non-boundary vert
  int randVert = RNG::RandomInt(numVerts);
  Vertex* ranVert = nonCorner->get(randVert);
  // get the move amount and distance before making a jump
  real moveLimit = EvolutionSettings::getInstance()->getMaxMovePercent();
  real distBeforeJump = EvolutionSettings::getInstance()->getDistBeforeJump();
  if(ranVert->getBoundary()) {
    // move along boundary line
    Array<Edge*>* boundaryEdges = new Array<Edge*>();
    for(int i=0;i<ranVert->getEdges()->getSize();i++)
      if(ranVert->getEdges()->get(i)->getIsBoundary())
        boundaryEdges->add(ranVert->getEdges()->get(i));
    // choose a random edge to move by
    int randDir = RNG::RandomInt(boundaryEdges->getSize());
    Edge* edgeToMoveBy = boundaryEdges->get(randDir);
    // get the edge length
    real length = edgeToMoveBy->length();
    // if the length is too small move the other direction
    // in the future this is going to check if it can jump i.e
    // it will jump around a corner.
    if(length < distBeforeJump) {
      for(int i=0;i<boundaryEdges->getSize();i++) {
        // this should always work since there should be at least
        // two boundary edges attached
        if(boundaryEdges->get(i)!=edgeToMoveBy) {
          edgeToMoveBy = boundaryEdges->get(i);
          i = boundaryEdges->getSize();
        }
      }
      // recheck length and abort if the check fails
      real length = edgeToMoveBy->length();
      if(length < distBeforeJump)
        return fracture;
    }
    // get a random mutation value
    real mutateScale = RNG::RandomFloat(moveLimit);
    // Get the two points on the edge to move on
    Point2 firstPoint = ranVert->getLocation();
    Point2 secondPoint = edgeToMoveBy->getOtherPoint(ranVert->getID());
    // calculate the vert's new location
    Point2 slope = secondPoint.minus(firstPoint);
    slope.scale(mutateScale);
    Point2 newLoc = firstPoint.add(slope);
    // set the new location
    ranVert->setLocation(newLoc);
    // tell the verts edges about its new location
    ranVert->updateEdges();
    // clean up
    while(boundaryEdges->getSize())
      boundaryEdges->removeLast();
    delete boundaryEdges;
  } else {
    // maybe implement move along edges ???
    // move about faces using barycentric coordinates
    // get the faces containing the point
    Array<Face*>* facesWithVert = fracture->getFacesWithVertex(ranVert);
    // create a face containing all points around the vert
    Face* faceToMutateAround = new Face();
    for(int i=0;i<facesWithVert->getSize();i++) {
      Face* tmp = facesWithVert->get(i);
      for(int j=0;j<tmp->getEdges()->getSize();j++)
        if(!tmp->getEdges()->get(j)->eitherMatch(ranVert->getID()))
          faceToMutateAround->getEdges()->add(tmp->getEdges()->get(j)->copy());
      for(int j=0;j<tmp->getVerts()->getSize();j++)
        if(tmp->getVerts()->get(j)->getID() != ranVert->getID())
          faceToMutateAround->getVerts()->add(tmp->getVerts()->get(j)->copy(faceToMutateAround->getEdges()));
    }
    // create the container for the generated Tris
    Array<Tri*>* generatedTris = new Array<Tri*>();
    // detect if the face is convex or not
    faceToMutateAround->detectIfConvex();
    if(faceToMutateAround->getIsConvex()) {
      // TODO :: Do this the more efficient way
      // convex case mutation (easy)
      // generate tris
      for(int i=0;i<faceToMutateAround->getEdges()->getSize();i++)
        generatedTris->add(new Tri(faceToMutateAround->getEdges()->get(i),ranVert->getLocation(),ranVert->getID()));
      // create barycentric coordinates for mutation (2 * #tris)
      // TODO :: Combine this with the case below
      int numBarys = generatedTris->getSize()*2;
      real barys[numBarys];
      for(int i=0;i<numBarys;i++)
        barys[i] = RNG::RandomFloat(moveLimit);
      // apply mutations
      Point2 newPos;
      newPos.xpos = 0.0;
      newPos.ypos = 0.0;
      int pointID = ranVert->getID();
      for(int i=0;i<generatedTris->getSize();i++) {
        // get new position
        real baryOne = barys[i*2];
        real baryTwo = barys[i*2-1];
        real baryThree = 1.0 - baryOne - baryTwo;
        newPos = generatedTris->get(i)->interpolatePosition(baryOne,baryTwo,baryThree);
        // update the position in all the remaining tris
        for(int j=i;j<generatedTris->getSize();j++)
          generatedTris->get(j)->updatePosition(pointID,newPos);
      }
      // set new position of vert
      ranVert->setLocation(newPos);
      // update edges
      ranVert->updateEdges();
      // clean up
    } else {
      // concave case mutation (harder)
      // create collection for trimesh shell
      Array<Vertex*>* vertsInView = new Array<Vertex*>();
      Array<Vertex*>* sortedVertsInView = new Array<Vertex*>();
      Array<Edge*>* trimeshShell = new Array<Edge*>();
      // get all verts in view
      for(int i=0;i<faceToMutateAround->getVerts()->getSize();i++) {
        Vertex* vert = faceToMutateAround->getVerts()->get(i);
        // create a temp edge to check for intersections
        Edge* tmpEdge = new Edge(ranVert->getLocation(),vert->getLocation());
        bool noIntersection = true;
        // check if intersections
        for(int i=0;i<faceToMutateAround->getEdges()->getSize();i++)
          if(faceToMutateAround->getEdges()->get(i)->intersects(tmpEdge))
            noIntersection = false;
        // if no intersections add it to the list of verts in view
        if(noIntersection)
          vertsInView->add(vert);
        // Note :: vert is still a copy
        // clean up
        delete tmpEdge;
      }
      // sort verts
      Array<Integer>* sortedIDs = faceToMutateAround->sortVertIDsByPath();
      for(int i=0;i<sortedIDs->getSize();i++)
        for(int j=0;j<vertsInView->getSize();i++)
          if(vertsInView->get(j)->getID() == sortedIDs->get(i).val) {
            sortedVertsInView->add(vertsInView->get(j));
            j = vertsInView->getSize();
          }
      // create shell from verts
      for(int i=0;i<sortedVertsInView->getSize();i++) {
        Vertex* one = sortedVertsInView->get(i);
        Vertex* two = i==sortedVertsInView->getSize()-1
          ? sortedVertsInView->get(0) : sortedVertsInView->get(i+1);
        Edge* newEdge = new Edge(one->getLocation(),two->getLocation(),one->getID(),two->getID());
        trimeshShell->add(newEdge);
      }
      // generate tris
      for(int i=0;i<trimeshShell->getSize();i++)
        generatedTris->add(new Tri(trimeshShell->get(i),ranVert->getLocation(),ranVert->getID()));
      // create barycentric coordinates for mutation (Only 2 for this case)
      // TODO :: Combine this with the case above
      //int numBarys = generatedTris->getSize()*2;
      int numBarys = 2;
      real barys[numBarys];
      for(int i=0;i<numBarys;i++)
        barys[i] = RNG::RandomFloat(moveLimit);
      // apply mutations
      Point2 newPos;
      newPos.xpos = 0.0;
      newPos.ypos = 0.0;

      int pointID = ranVert->getID();
      int ranTri = RNG::RandomInt(generatedTris->getSize());

      //for(int i=0;i<generatedTris->getSize();i++) {

      // get new position
      //real baryOne = barys[i*2];
      //real baryTwo = barys[i*2-1];
      real baryOne = barys[0];
      real baryTwo = barys[1];
      real baryThree = 1.0 - baryOne - baryTwo;
      newPos = generatedTris->get(ranTri)->interpolatePosition(baryOne,baryTwo,baryThree);

      // update the position in all the remaining tris (skip for this step)
      //  for(int j=i;j<generatedTris->getSize();j++)
      //    generatedTris->get(j)->updatePosition(pointID,newPos);

      //}

      // set new position of vert
      ranVert->setLocation(newPos);
      // update edges
      ranVert->updateEdges();
      // clean up
      while(vertsInView->getSize())
        vertsInView->removeLast();
      while(sortedIDs->getSize())
        sortedIDs->removeLast();
      while(sortedVertsInView->getSize())
        sortedVertsInView->removeLast();
      while(trimeshShell->getSize())
        delete trimeshShell->removeLast();
      delete vertsInView;
      delete trimeshShell;
      delete sortedVertsInView;
      delete sortedIDs;
    }
    // clean up
    while(nonCorner->getSize())
      nonCorner->removeLast();
    while(facesWithVert->getSize())
      facesWithVert->removeLast();
    while(generatedTris->getSize())
      delete generatedTris->removeLast();
    while(faceToMutateAround->getVerts()->getSize())
      delete faceToMutateAround->getVerts()->removeLast();
    while(faceToMutateAround->getEdges()->getSize())
      delete faceToMutateAround->getEdges()->removeLast();
    delete faceToMutateAround;
    delete generatedTris;
    delete facesWithVert;
    delete nonCorner;
  }
  return fracture;
}
