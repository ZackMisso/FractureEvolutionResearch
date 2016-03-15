#include "face.h"
#include "rng.h"
#include "debug.h"
#include "debugController.h"

#include <cstdlib>

#include <iostream>

using namespace std;

Face::Face() {
  triMesh = new Array<Face*>();
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  id = DebugController::getNextFace();
  selected = false;
}

Face::Face(Array<Vertex*>* verts) {
  triMesh = new Array<Face*>();
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  id = DebugController::getNextFace();
  selected = false;
}

Face::~Face() {
  while(verts->getSize())
    verts->removeLast();
  while(edges->getSize())
    edges->removeLast();
  delete verts;
  delete edges;
}

bool Face::contains(float x,float y) {
  Point2 p;
  p.xpos = x;
  p.ypos = y;
  return contains(p);
}

// this must work for polygons of any size
bool Face::contains(Point2 point) {
  int intersections = 0;
  // create horizontal ray
  Edge *ray = new Edge(-1.0f,point.ypos,point.xpos,point.ypos);
  // get the number of intersections
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->intersects(ray))
      intersections++;
  // if odd this face contains the point
  delete ray;
  return intersections % 2;
}

bool Face::contains(Vertex* vert) {
  for(int i=0;i<verts->getSize();i++)
    if(vert==verts->get(i))
      return true;
  return false;
}

bool Face::contains(Edge* edge) {
  for(int i=0;i<edges->getSize();i++)
    if(edge==edges->get(i))
      return true;
  return false;
}

// THIS METHOD IS PROBABLY INCORRECT
Array<Face*>* Face::separate(Vertex* newVert) {
  Array<Face*>* newFaces = new Array<Face*>();
  verts->add(newVert);

  // verts will always be >= 3 in size
  int indexOne = rand() % verts->getSize();
  int indexTwo = rand() % verts->getSize();

  float* tmp = 0x0;

  while(indexOne == indexTwo)
    indexTwo = rand() % verts->getSize();

  Point2 oneLoc = verts->get(indexOne)->getLocation();
  Point2 twoLoc = verts->get(indexTwo)->getLocation();

  Edge* edgeOne = new Edge(oneLoc,newVert->getLocation());
  Edge* edgeTwo = new Edge(newVert->getLocation(),twoLoc);

  Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();

  oneEdges->add(edgeOne);
  oneEdges->add(edgeTwo);
  twoEdges->add(edgeOne);
  twoEdges->add(edgeTwo);

  findSeparatePaths(oneEdges,twoEdges,oneLoc,twoLoc);

  Array<Vertex*>* oneVerts = findVertsOnPath(oneEdges);
  Array<Vertex*>* twoVerts = findVertsOnPath(twoEdges);

  Face* oneFace = new Face();
  oneFace->setVerts(oneVerts);
  oneFace->setEdges(oneEdges);

  Face* twoFace = new Face();
  twoFace->setVerts(twoVerts);
  twoFace->setEdges(twoEdges);

  newFaces->add(oneFace);
  newFaces->add(twoFace);

  return newFaces;
}

Array<Face*>* Face::separate(float x,float y) {
  Array<Face*>* newFaces = new Array<Face*>();
  int numSeperations = RNG::RandomInt(2,edges->getSize(),4);
  // do the first two seperations
  Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();
  Array<Vertex*>* oneVerts = new Array<Vertex*>();
  Array<Vertex*>* twoVerts = new Array<Vertex*>();

  Vertex* sharedPoint = new Vertex(x,y);
  oneVerts->add(sharedPoint);
  twoVerts->add(sharedPoint);

  Point2 oneLoc;
  Point2 twoLoc;

  int edgeIndOne = -1;

  Array<Edge*>* tmpEdges = new Array<Edge*>();
  Array<Edge*>* edgesToRemove = new Array<Edge*>();

  for(int i=0;i<2;i++) {
    int edgeInd;
    if(edgeIndOne==-1) {
      edgeInd = RNG::RandomInt(edges->getSize());
      edgeIndOne = edgeInd;
    } else
      edgeInd = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);

    float edgeDist = RNG::RandomFloat();
    Edge* edge = edges->get(edgeInd);
    Point2 newPoint = edge->getPointBetween(edgeDist);
    Edge* newEdge = new Edge(x,y,newPoint.xpos,newPoint.ypos);
    Edge* intersector = newEdge->intersects(edges,edge);
    if(intersector){
      newPoint = intersector->getIntersectionPoint(newEdge);
      delete newEdge;
      newEdge = new Edge(x,y,newPoint.xpos,newPoint.ypos);
      edge = intersector;
    }
    DebugController::writeCreateEdge(newEdge);
    edge->split(tmpEdges,newPoint);

    if(i) {
      oneLoc.xpos = newPoint.xpos;
      oneLoc.ypos = newPoint.ypos;
    } else {
      twoLoc.xpos = newPoint.xpos;
      twoLoc.ypos = newPoint.ypos;
    }

    Vertex* newVert = new Vertex(newPoint);
    DebugController::writeCreateVert(newVert);
    oneVerts->add(newVert);
    twoVerts->add(newVert);

    oneEdges->add(newEdge);
    twoEdges->add(newEdge);
    edgesToRemove->add(edge);

    numSeperations--;
  }
  while(tmpEdges->getSize())
    edges->add(tmpEdges->removeLast());
  while(edgesToRemove->getSize()) {
    DebugController::writeDeleteEdge(edgesToRemove->get(edgesToRemove->getSize()-1));
    edges->remove(edgesToRemove->removeLast());
  }
  delete edgesToRemove;
  delete tmpEdges;

  findSeparatePaths(oneEdges,twoEdges,oneLoc,twoLoc);
  Array<Vertex*>* tmpOne = findVertsOnPath(oneEdges);
  Array<Vertex*>* tmpTwo = findVertsOnPath(twoEdges);

  while(tmpOne->getSize())
    oneVerts->add(tmpOne->removeLast());
  while(tmpTwo->getSize())
    twoVerts->add(tmpTwo->removeLast());

  delete tmpOne;
  delete tmpTwo;

  Face* oneFace = new Face();
  oneFace->setVerts(oneVerts);
  oneFace->setEdges(oneEdges);
  DebugController::writeCreateFace(oneFace);

  Face* twoFace = new Face();
  twoFace->setVerts(twoVerts);
  twoFace->setEdges(twoEdges);
  DebugController::writeCreateFace(twoFace);

  newFaces->add(oneFace);
  newFaces->add(twoFace);

  // do the remaining separations
  while(numSeperations) {
    // to be implemented
    numSeperations--;
  }
  return newFaces;
}

void Face::clearTrimesh() {
  triMesh->clear();
}

void Face::splitIntoTrimesh() {
  // to be implemented
}

void Face::detectIfConvex() { // Need To Test
  Array<Point>* hull = getConvexHull();
  if(hull->getSize() != verts->getSize())
    isConvex = false;
  else {
    // O(N^2) This can be Faster
    int counter=0;
    for(int i=0;i<verts->getSize();i++)
      for(int j=0;j<hull->getSize();j++)
        if(verts->get(i)->getLocation().xpos == hull->get(j).xpos)
          if(verts->get(i)->getLocation().ypos == hull->get(j).ypos)
            counter++;
    isConvex=counter==verts->getSize();
  }
}

// Simple Gift Wrapping Algorithm
Array<Point2>* Face::getConvexHull() { // Need to Test
  // Set Up Variables
  Array<Point2>* hull = new Array<Point2>(verts->getSize()+1);
  Array<Point2>* contents = new Array<Point2>(verts->getSize()+1);
  for(int i=0;i<verts->getSize();i++)
    contents->add(verts->get(i));
  Point2 pointOnHull;
  Point2 lastPoint;
  Point2 endpoint;
  // Get LeftMost Point
  for(int i=0;i<contents->getSize();i++)
    if(pointOnHull.xpos > contents->get(i)->getLocation().xpos)
      endPoint = contents->get(i)->getLocation();
  lastPoint = endPoint;
  // Find the Leftmost point then add until found convex hull
  while(!lastPoint.equals(endpoint)||!hull->getSize()) {
    pointOnHull = contents->get(0);
    for(int i=1;i<contents->getSize();i++) {
      Edge* edgeOne = new Edge(lastPoint,pointOnHull);
      Edge* edgeTwo = new Edge(lastPoint,contents->get(i));
      if(edgeOne->determinant(edgeTwo) > 0)
        pointOnHull = contents->get(i);
      delete edgeOne;
      delete edgeTwo;
    }
    lastPoint = pointOnHull;
    hull->add(pointOnHull);
    contents->remove(pointOnHull);
  }
}

// this may also need different forms of implementations
//Array<Face*>* Face::separate(Point2 newPoint) {
//  // to be implemented
//  return 0x0;
//}

//Array<Face*>* Face::separate(Point2 start,Point2 end) {
//  // to be implemented
//  return 0x0;
//}

void Face::findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc) {
  Edge* startOne = 0x0;
  Edge* startTwo = 0x0;
  Edge* errorFinder = 0x0;
  Array<Edge*>* tmpArray = new Array<Edge*>();
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->eitherMatch(oneLoc))
      tmpArray->add(edges->get(i));
  Edge* on = tmpArray->get(0);
  Point2 poi = on->getOtherPoint(oneLoc);
  one->add(on);
  Point2 prev = oneLoc;
  while(poi.xpos != twoLoc.xpos || poi.ypos != twoLoc.ypos) {
    Edge* tmpe = 0x0;
    for(int i=0;i<edges->getSize();i++)
      if(edges->get(i)->eitherMatch(poi) && !edges->get(i)->eitherMatch(prev))
        tmpe = edges->get(i);
    one->add(tmpe);
    prev.xpos = poi.xpos;
    prev.ypos = poi.ypos;
    poi = tmpe->getOtherPoint(poi);
  }

  on = tmpArray->get(1);
  poi = on->getOtherPoint(oneLoc);
  two->add(on);
  prev = oneLoc;
  while(poi.xpos != twoLoc.xpos || poi.ypos != twoLoc.ypos) {
    Edge* tmpe = 0x0;
    for(int i=0;i<edges->getSize();i++)
      if(edges->get(i)->eitherMatch(poi) && !edges->get(i)->eitherMatch(prev))
        tmpe = edges->get(i);
    two->add(tmpe);
    prev.xpos = poi.xpos;
    prev.ypos = poi.ypos;
    poi = tmpe->getOtherPoint(poi);
  }
}

Array<Vertex*>* Face::findVertsOnPath(Array<Edge*>* edgs) {
  // this should be fixed so that it only needs to check the first one's location
  Array<Vertex*>* vp = new Array<Vertex*>();

  for(int i=0;i<edgs->getSize();i++)
    for(int j=0;j<verts->getSize();j++) {
      if(edgs->get(i)->getFirst().xpos == verts->get(j)->getLocation().xpos && edgs->get(i)->getFirst().ypos == verts->get(j)->getLocation().ypos)
        if(!vp->contains(verts->get(j))){
          vp->add(verts->get(j));
          j = verts->getSize();
        }
      if(j!=verts->getSize())
        if(edgs->get(i)->getSecond().xpos == verts->get(j)->getLocation().xpos && edgs->get(i)->getSecond().ypos == verts->get(j)->getLocation().ypos)
          if(!vp->contains(verts->get(j))){
            vp->add(verts->get(j));
            j = verts->getSize();
          }
    }
  return vp;
}

Array<Vertex*>* Face::getVerts() { return verts; }
Array<Edge*>* Face::getEdges() { return edges; }
int Face::getID() { return id; }
bool Face::getSelected() { return selected; }
bool Face::getIsConvex() { return isConvex; }

void Face::setVerts(Array<Vertex*>* param) { verts = param; }
void Face::setEdges(Array<Edge*>* param) { edges = param; }
void Face::setID(int param) { id = param; }
void Face::setSelected(bool param) { selected = param; }
void Face::setIsConvex(bool param) { isConvex = param; }
