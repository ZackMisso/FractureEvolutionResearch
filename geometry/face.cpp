#include "face.h"
#include "../misc/rng.h"
#include "../test/debug.h"
#include "../test/debugController.h"

#include <cstdlib>

#include <iostream>

using namespace std;

Face::Face() {
  triMesh = new Array<Tri*>();
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  id = -1;
  selected = false;
}

Face::Face(Array<Vertex*>* verts) {
  triMesh = new Array<Tri*>();
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  id = -1;
  selected = false;
}

Face::~Face() {
  while(triMesh->getSize())
    delete triMesh->removeLast();
  while(verts->getSize())
    verts->removeLast();
  while(edges->getSize())
    edges->removeLast();
  delete verts;
  delete edges;
}

bool Face::contains(real x,real y) {
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
// TODO :: REWRITE THIS METHOD
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

Array<Face*>* Face::separate(real x,real y) {
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

    real edgeDist = RNG::RandomFloat();
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
  while(triMesh->getSize())
    delete triMesh->removeLast();
}

real Face::area() {
  real area = 0.0;
  for(int i=0;i<triMesh->getSize();i++)
    area += triMesh->get(i)->area();
  return area;
}

Array<Point2>* Face::sortPointsByPath() {
  Array<Point2>* sortedPoints = new Array<Point2>();
  Edge* edge = edges->get(0);
  Point2 start = edge->getFirst();
  Point2 current = edge->getFirst();
  Point2 next = edge->getSecond();
  //cout << "Before While Loop" << endl;
  while(next.xpos != start.xpos || next.ypos != start.ypos) {
    //cout << "IN WHILE LOOP" << endl;
    sortedPoints->add(current);
    //cout << "Current :: ";
    //current.debug();
    //cout << "Next :: ";
    //next.debug();
    bool chk = false;
    for(int i=0;i<edges->getSize();i++)
      if(edges->get(i)->eitherMatch(next) && edges->get(i) != edge) {
        edge = edges->get(i);
        current = next;
        next = edge->getOtherPoint(next);
        i=edges->getSize();
        chk=true;
      }
    if(!chk)
      cout << "ERROR IN SORT POINTS BY PATH" << endl;
  }
  sortedPoints->add(current);
  return sortedPoints;
}

void Face::splitIntoTrimesh() {
  detectIfConvex();
  // clear previous triMesh if it exists
  while(triMesh->getSize())
    delete triMesh->removeLast();
  if(isConvex)
    splitIntoTrimeshConvex();
  else
    splitIntoTrimeshConcave();
}

void Face::splitIntoTrimeshConvex() {
  while(triMesh->getSize())
    delete triMesh->removeLast();
  Array<Point2>* points = sortPointsByPath();
  // Garunteed to have at least 3 points
  Point2 one = points->get(0);
  Point2 two = points->get(1);
  Point2 three = points->get(2);
  triMesh->add(new Tri(one,two,three));
  int counter=3;
  for(;counter<points->getSize();counter++) {
    two = points->get(counter-1);
    three = points->get(counter);
    triMesh->add(new Tri(one,two,three));
  }
  delete points;
}

// THIS BECOMES AN ISSUE WHEN SPLITTING A POLYGON WITH HOLES
void Face::splitIntoTrimeshConcave() { // REWRITE
  clearTrimesh();
  Array<Point2>* points = sortPointsByPath();
  if(isClockwise(points))
    points = reversePath(points);
  bool separating = true;
  while(separating) {
    separating = false;
    for(int i=0;i<points->getSize();i++) {
      Point2 current = points->get(i);
      Point2 next,prev;
      int nextI,prevI;
      if(i==0) {
        prev = points->get(points->getSize()-1);
        prevI = points->getSize()-1;
      } else {
        prev = points->get(i-1);
        prevI = i-1;
      } if(i==points->getSize()-1) {
        next = points->get(0);
        nextI = 0;
      } else {
        next = points->get(i+1);
        nextI = i+1;
      }
      // bary logic that will be used for mutations
      Point2 wedgeOne = Point2(prev.xpos-current.xpos,prev.ypos-current.ypos);
      Point2 wedgeTwo = Point2(next.xpos-current.xpos,next.ypos-current.ypos);
      if(wedgeOne.wedgeProduct(wedgeTwo) > 0) {
        // the point is an interior angle
        bool containsOtherVert = false;
        Point2 v0 = Point2(next.xpos-current.xpos,next.ypos-current.ypos);
        Point2 v1 = Point2(prev.xpos-current.xpos,prev.ypos-current.ypos);
        for(int j=0;j<points->getSize();j++) {
          if(j != i && j != nextI && j != prevI) {
            Point2 point = points->get(j);
            Point2 v2 = Point2(point.xpos-current.xpos,point.ypos-current.ypos);
            real v0dotv0 = v0.dot(v0);
            real v1dotv1 = v1.dot(v1);
            real v1dotv0 = v1.dot(v0);
            real v2dotv0 = v2.dot(v0);
            real v2dotv1 = v2.dot(v1);
            real div = (v0dotv0 * v1dotv1) - (v1dotv0*v1dotv0);
            if(div != 0.0) {
              real u = (v1dotv1*v2dotv0) - (v1dotv0*v2dotv1) / div;
              real v = (v0dotv0*v2dotv1) - (v1dotv0*v2dotv0) / div;
              if(u<0.0f || v <0.0f || u+v > 1.0f)
                containsOtherVert = false;
              else {
                containsOtherVert = true;
                j = points->getSize();
              }
            }
          }
        }
        if(!containsOtherVert) {
          // add triangle
          triMesh->add(new Tri(current,prev,next));
          points->remove(i);
          i--;
          separating = true;
        }
      }
    }
  }
  points->clear();
  delete points;
}

bool Face::isClockwise(Array<Point2>* sortedPath) {
  float sum = 0.0f;
  for(int i=1;i<sortedPath->getSize();i++)
    sum += (sortedPath->get(i).xpos-sortedPath->get(i-1).xpos) *
      (sortedPath->get(i).ypos + sortedPath->get(i-1).ypos);
  return sum > 0.0f;
}

Array<Point2>* Face::reversePath(Array<Point2>* sortedPath) {
  Array<Point2>* reversedPath = new Array<Point2>(sortedPath->getSize()+1);
  while(sortedPath->getSize())
    reversedPath->add(sortedPath->removeLast());
  delete sortedPath;
  return reversedPath;
}

void Face::detectIfConvex() {
  Array<Point2>* hull = getConvexHull();
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
Array<Point2>* Face::getConvexHull() {
  // Set Up Variables
  Array<Point2>* hull = new Array<Point2>(verts->getSize()+1);
  Array<Point2>* contents = new Array<Point2>(verts->getSize()+1);
  for(int i=0;i<verts->getSize();i++)
    contents->add(verts->get(i)->getLocation());
  Point2 pointOnHull;
  Point2 lastPoint;
  Point2 endpoint = contents->get(0);
  // Get LeftMost Point
  for(int i=1;i<contents->getSize();i++)
    if(endpoint.xpos > contents->get(i).xpos)
      endpoint = contents->get(i);
  lastPoint = endpoint;
  // Find the Leftmost point then add until found convex hull
  while(!lastPoint.equals(endpoint)||!hull->getSize()) {
    int ind = 0;
    pointOnHull = contents->get(0);
    for(int i=1;i<contents->getSize();i++) {
      Edge* edgeOne = new Edge(lastPoint,pointOnHull);
      Edge* edgeTwo = new Edge(lastPoint,contents->get(i));
      if(edgeOne->determinant(edgeTwo) > 0) {
        ind = i;
        pointOnHull = contents->get(i);
      }
      delete edgeOne;
      delete edgeTwo;
    }
    lastPoint = pointOnHull;
    hull->add(pointOnHull);
    contents->remove(ind);
  }
  return hull;
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

void Face::draw() {
  // to be implemented
}

Array<Tri*>* Face::getTriMesh() { return triMesh; }
Array<Vertex*>* Face::getVerts() { return verts; }
Array<Edge*>* Face::getEdges() { return edges; }
int Face::getID() { return id; }
bool Face::getSelected() { return selected; }
bool Face::getIsConvex() { return isConvex; }

void Face::setTriMesh(Array<Tri*>* param) { triMesh = param; }
void Face::setVerts(Array<Vertex*>* param) { verts = param; }
void Face::setEdges(Array<Edge*>* param) { edges = param; }
void Face::setID(int param) { id = param; }
void Face::setSelected(bool param) { selected = param; }
void Face::setIsConvex(bool param) { isConvex = param; }
