#include "face.h"
#include "../misc/rng.h"
#include "../test/debug.h"
#include "../test/debugController.h"
#include "../dataStructures/integer.h"
#include <cstdlib>
#include <vector>
#include <algorithm>

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

Face* Face::copy(Array<Vertex*>* newVerts,Array<Edge*>* newEdges) {
  Face* face = new Face();
  face->setID(id);
  face->setSelected(selected);
  for(int i=0;i<verts->getSize();i++) {
    Vertex* newVert = 0x0;
    int idd = verts->get(i)->getID();
    for(int j=0;j<newVerts->getSize();j++)
      if(idd == newVerts->get(j)->getID()) {
        newVert = newVerts->get(j);
        j = newVerts->getSize();
      }
    face->getVerts()->add(newVert);
  }
  for(int i=0;i<edges->getSize();i++) {
    Edge* newEdge = 0x0;
    int idd = edges->get(i)->getID();
    for(int j=0;j<newEdges->getSize();j++)
      if(idd == newEdges->get(j)->getID()) {
        newEdge = newEdges->get(j);
        j = newEdges->getSize();
      }
    face->getEdges()->add(newEdge);
  }
  return face;
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
    if(vert->getLocation().equals(verts->get(i)->getLocation()))
      return true;
  return false;
}

bool Face::contains(Edge* edge) {
  for(int i=0;i<edges->getSize();i++)
    if(edge==edges->get(i))
      return true;
  return false;
}

// This should only be called from a mutation
// Assumptions ::
// Vertex has already been given a consistent id
// detectIfConvex has already been called
// TODO :: Make This Cleaner
Array<Face*>* Face::separate(Vertex* newVert,IDTracker* ids) {
  // create the list of new faces
  Array<Face*>* newFaces = new Array<Face*>();
  // get number of separations
  //int numSeperations = RNG::RandomInt(2,edges->getSize(),4);
  int numSeparations = 1;
  // create required data structures
  Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();
  Array<Vertex*>* oneVerts = new Array<Vertex*>();
  Array<Vertex*>* twoVerts = new Array<Vertex*>();
  // add new vert to both new adds
  cout << "Adding New Vertex to Verts: ";
  DebugController::writeVertState(newVert);
  oneVerts->add(newVert);
  twoVerts->add(newVert);
  // create data structures for new edge generation
  Array<Edge*>* newEdges = new Array<Edge*>();
  Array<Edge*>* edgesToRemove = new Array<Edge*>();
  Vertex* newVertOne = 0x0;
  Vertex* newVertTwo = 0x0;
  Edge* edgeOne = 0x0;
  Edge* edgeTwo = 0x0;
  if(isConvex) {
    // convex case (easy)
    cout << "Inside Convex Case In Face Split" << endl;
    // choose two random edges
    int edgeIndOne = RNG::RandomInt(edges->getSize());
    int edgeIndTwo = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);
    edgeOne = edges->get(edgeIndOne);
    edgeTwo = edges->get(edgeIndTwo);
    // choose two random locations on those edges
    real edgeDistOne = RNG::RandomFloat();
    real edgeDistTwo = RNG::RandomFloat();
    cout << "Chose Random Locations: " << edgeDistOne << " and " << edgeDistTwo << endl;
    // get the two points on the edges
    Point2 newPointOne = edgeOne->getPointBetween(edgeDistOne);
    cout << "New Point One: ";
    DebugController::writePointState(newPointOne);
    Point2 newPointTwo = edgeTwo->getPointBetween(edgeDistTwo);
    cout << "New Point Two: ";
    DebugController::writePointState(newPointTwo);
    // create the new verts
    newVertOne = new Vertex(newPointOne);
    newVertTwo = new Vertex(newPointTwo);
    newVertOne->setID(ids->incrementNextVert());
    newVertTwo->setID(ids->incrementNextVert());
    cout << "Creating New Edge Vert One: ";
    DebugController::writeVertState(newVertOne);
    cout << "Creating New Edge Vert Two: ";
    DebugController::writeVertState(newVertTwo);
  } else {
    // concave case (harder)
    // choose two random edges
    int edgeIndOne = RNG::RandomInt(edges->getSize());
    int edgeIndTwo = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);
    edgeOne = edges->get(edgeIndOne);
    edgeTwo = edges->get(edgeIndTwo);
    // choose two random locations on those edges
    real edgeDistOne = RNG::RandomFloat();
    real edgeDistTwo = RNG::RandomFloat();
    // get the two points on the edges
    Point2 newPointOne = edgeOne->getPointBetween(edgeDistOne);
    Point2 newPointTwo = edgeTwo->getPointBetween(edgeDistTwo);
    // create temporary edges to test intersection
    Edge* tmpEdgeOne = new Edge(newVert->getLocation().xpos,newVert->getLocation().ypos,newPointOne.xpos,newPointOne.ypos);
    Edge* tmpEdgeTwo = new Edge(newVert->getLocation().xpos,newVert->getLocation().ypos,newPointTwo.xpos,newPointTwo.ypos);
    // try to find intersectors
    Edge* intersectorOne = tmpEdgeOne->intersects(edges,edgeOne);
    Edge* intersectorTwo = tmpEdgeTwo->intersects(edges,edgeTwo);
    // react if there are intersectors
    if(intersectorOne) {
      newPointOne = intersectorOne->getIntersectionPoint(tmpEdgeOne);
      delete tmpEdgeOne;
      edgeOne = intersectorOne;
    }if(intersectorTwo) {
      newPointTwo = intersectorTwo->getIntersectionPoint(tmpEdgeTwo);
      delete tmpEdgeTwo;
      edgeTwo = intersectorTwo;
    }
    // create the new verts
    newVertOne = new Vertex(newPointOne);
    newVertTwo = new Vertex(newPointTwo);
    newVertOne->setID(ids->incrementNextVert());
    newVertTwo->setID(ids->incrementNextVert());
  }
  // add edges to remove
  edgesToRemove->add(edgeOne);
  edgesToRemove->add(edgeTwo);
  // split old edges
  edgeOne->split(newEdges,newVertOne->getLocation(),newVertOne->getID(),ids);
  edgeTwo->split(newEdges,newVertTwo->getLocation(),newVertTwo->getID(),ids);
  cout << "Number Of New Edges: " << newEdges->getSize() << endl;
  // remove old edges
  cout << "Removing Old Edges" << endl;
  edges->remove(edgeOne);
  edges->remove(edgeTwo);
  delete edgeOne;
  delete edgeTwo;
  // create new edges that will be separating
  Edge* separateEdgeOne = new Edge(newVertOne->getLocation(),newVert->getLocation(),newVertOne->getID(),newVert->getID());
  Edge* separateEdgeTwo = new Edge(newVert->getLocation(),newVertTwo->getLocation(),newVert->getID(),newVertTwo->getID());
  separateEdgeOne->setID(ids->incrementNextEdge());
  separateEdgeTwo->setID(ids->incrementNextEdge());
  cout << "Creating The First New Separating Edge" << endl;
  DebugController::writeEdgeState(separateEdgeOne);
  cout << "Creating The Second New Separating Edge" << endl;
  DebugController::writeEdgeState(separateEdgeTwo);
  // add new edges to face
  cout << "Adding New Edges" << endl;
  while(newEdges->getSize())
    edges->add(newEdges->removeLast());
  delete newEdges;
  cout << "Finding The Separate Paths" << endl;
  // find two separate paths
  findSeparatePaths(oneEdges,twoEdges,newVertOne->getLocation(),newVertTwo->getLocation());
  oneEdges->add(separateEdgeOne);
  oneEdges->add(separateEdgeTwo);
  twoEdges->add(separateEdgeOne);
  twoEdges->add(separateEdgeTwo);
  // get the verts on the paths
  oneVerts = findVertsOnPath(oneEdges);
  twoVerts = findVertsOnPath(twoEdges);
  // add new verts to both vert list
  oneVerts->add(newVert);
  oneVerts->add(newVertOne);
  oneVerts->add(newVertTwo);
  twoVerts->add(newVert);
  twoVerts->add(newVertOne);
  twoVerts->add(newVertTwo);
  // delete the references to the old face
  for(int i=0;i<oneEdges->getSize();i++)
    for(int k=0;k<oneEdges->get(i)->getFaceIDs()->getSize();k++)
      if(oneEdges->get(i)->getFaceIDs()->get(k).val == id)
        oneEdges->get(i)->getFaceIDs()->remove(k);
  for(int i=0;i<twoEdges->getSize();i++)
    for(int k=0;k<twoEdges->get(i)->getFaceIDs()->getSize();k++)
      if(twoEdges->get(i)->getFaceIDs()->get(k).val == id)
        twoEdges->get(i)->getFaceIDs()->remove(k);
  // create the two new faces
  Face* oneFace = new Face();
  oneFace->setID(ids->incrementNextFace());
  oneFace->setVerts(oneVerts);
  oneFace->setEdges(oneEdges);
  Face* twoFace = new Face();
  twoFace->setID(ids->incrementNextFace());
  twoFace->setVerts(twoVerts);
  twoFace->setEdges(twoEdges);
  // add reference to new face to edges
  for(int i=0;i<oneEdges->getSize();i++)
    oneEdges->get(i)->getFaceIDs()->add(Integer(oneFace->getID()));
  for(int i=0;i<twoEdges->getSize();i++)
    twoEdges->get(i)->getFaceIDs()->add(Integer(twoFace->getID()));
  // updates face references in verts
  for(int i=0;i<oneVerts->getSize();i++)
    oneVerts->get(i)->updateFaceIDs();
  for(int i=0;i<twoVerts->getSize();i++)
    twoVerts->get(i)->updateFaceIDs();
  // add to array of faces
  newFaces->add(oneFace);
  newFaces->add(twoFace);
  cout << "First Face ::" << endl;
  cout << "Number of Edges: " << oneFace->getEdges()->getSize() << endl;
  for(int i=0;i<oneFace->getEdges()->getSize();i++)
    DebugController::writeEdgeState(oneFace->getEdges()->get(i));
  cout << "Number of Verts: " << oneFace->getVerts()->getSize() << endl;
  for(int i=0;i<oneFace->getVerts()->getSize();i++)
    DebugController::writeVertState(oneFace->getVerts()->get(i));
  cout << "Second Face ::" << endl;
  cout << "Number of Edges: " << twoFace->getEdges()->getSize() << endl;
  for(int i=0;i<twoFace->getEdges()->getSize();i++)
    DebugController::writeEdgeState(twoFace->getEdges()->get(i));
  cout << "Number of Verts: " << twoFace->getVerts()->getSize() << endl;
  for(int i=0;i<twoFace->getVerts()->getSize();i++)
    DebugController::writeVertState(twoFace->getVerts()->get(i));
  // return array of faces
  return newFaces;
}

Array<Face*>* Face::separate(real x,real y) {
  cout << "Using Deprecated Method :: Face::separate" << endl;
  return 0x0;
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

Array<Integer>* Face::sortVertIDsByPath() {
  Array<Integer>* ids = new Array<Integer>();
  Array<Point2>* points = sortPointsByPath();
  for(int i=0;i<points->getSize();i++)
    for(int j=0;j<verts->getSize();j++)
      if(verts->get(j)->isMatch(points->get(i))) {
        ids->add(Integer(verts->get(j)->getID()));
        j = verts->getSize();
      }
  points->clear();
  delete points;
  return ids;
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
// Triangulation by Ear Clipping
void Face::splitIntoTrimeshConcave() { // REWRITE
  clearTrimesh();
  cout << "Num Verts: " << verts->getSize() << endl;
  Array<Point2>* points = sortPointsByPath();
  cout << "Points Size: " << points->getSize() << endl;
  for(int i=0;i<points->getSize();i++) {
    cout << "Point Pre Reverse :: " << i << " ";
    DebugController::writePointState(points->get(i));
  }
  if(!isClockwise(points))
    points = reversePath(points);
  cout << "Points Size After Reverse: " << points->getSize() << endl;
  for(int i=0;i<points->getSize();i++) {
    cout << "Point :: " << i << " ";
    DebugController::writePointState(points->get(i));
  }
  cout << "Correct up to here" << endl;

  while(points->getSize()>3) {
    for(int i=0;i<points->getSize();i++) {
      // get next and previous point
      int prev = i==0 ? points->getSize()-1 : i-1;
      int next = i==points->getSize()-1 ? 0 : i+1;
      // create two edges going from current point
      Edge* one = new Edge(points->get(i),points->get(next));
      Edge* two = new Edge(points->get(i),points->get(prev));
      // get their interiorAngle
      real interiorAngle = one->interiorAngle(two);
      // make sure it is not a reflex angle.
      if(interiorAngle < PI) {
          // create the triangle
          Tri* tri = new Tri(points->get(prev),points->get(i),points->get(next));
          bool isEar = true;
          for(int j=0;j<points->getSize();j++)
            if(j != i && j != prev && j != next)
              // test if the triangle is valid by making sure no verts are within it
              if(tri->isInside(points->get(j))) {
                isEar = false;
                j = points->getSize();
              }
          if(isEar) {
            triMesh->add(tri);
            points->remove(i);
            i = points->getSize();
          } else {
            delete tri;
          }
      }
      delete two;
      delete one;
    }
  }
  triMesh->add(new Tri(points->get(0),points->get(1),points->get(2)));
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
  if(hull->getSize() != verts->getSize()) {
    cout << "Size MisMatch" << endl;
    cout << "Hull Size: " << hull->getSize() << endl;
    isConvex = false;
  }
  else {
    // O(N^2) This can be Faster
    int counter=0;
    for(int i=0;i<verts->getSize();i++)
      for(int j=0;j<hull->getSize();j++)
        if(verts->get(i)->getLocation().xpos == hull->get(j).xpos)
          if(verts->get(i)->getLocation().ypos == hull->get(j).ypos)
            counter++;
    cout << "Counter: " << counter << endl;
    isConvex=counter==verts->getSize();
  }
}

real Face::cross(const Point2& o,const Point2& a,const Point2& b) {
  return (a.xpos-o.xpos)*(b.ypos-o.ypos)-(a.ypos-o.ypos)*(b.xpos-o.xpos);
}

// Andrew's monotone chain 2D convex hull Algorithm
// code is a modified version of what was provided here ::
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
Array<Point2>* Face::getConvexHull() {
  //Array<Point2>* contents = new Array<Point2>(verts->getSize()*2+1);
  int n = verts->getSize();
  int k = 0;
  vector<Point2> hull(2*n);
  vector<Point2> tmpVerts(n);
  for(int i=0;i<verts->getSize();i++) {
    tmpVerts[i] = verts->get(i)->getLocation();
    verts->get(i)->getLocation().debug();
  }
  cout << "DONE" << endl;
  for(int i=0;i<tmpVerts.size();i++)
    tmpVerts[i].debug();
  cout << "DoneToo" << endl;
  // sort points lexicographically
  sort(tmpVerts.begin(),tmpVerts.end());
  // build lower hull
  for(int i=0;i<n;i++) {
    while(k>=2 && cross(hull[k-2],hull[k-1],tmpVerts[i]) <= 0)
      k--;
    hull[k++] = tmpVerts[i];
  }
  // build upper hull
  for(int i=n-2,t=k+1;i>=0;i--) {
    while(k>=t && cross(hull[k-2],hull[k-1],tmpVerts[i]) <= 0)
      k--;
    hull[k++] = tmpVerts[i];
  }
  hull.resize(k-1);
  // convert hull vector to array
  Array<Point2>* points = new Array<Point2>();
  for(int i=0;i<hull.size();i++) {
    points->add(hull[i]);
    points->get(i).debug();
  }
  return points;
}

// Simple Gift Wrapping Algorithm
Array<Point2>* Face::getConvexHullOld() {

  // Set Up Variables
  cout << "Verts Size: " << verts->getSize() << endl;
  Array<Point2>* hull = new Array<Point2>(verts->getSize()+1);
  Array<Point2>* contents = new Array<Point2>(verts->getSize()+1);
  for(int i=0;i<verts->getSize();i++)
    contents->add(verts->get(i)->getLocation());
  Point2 pointOnHull;
  Point2 lastPoint;
  Point2 endpoint = contents->get(0);
  // Get LeftMost Point
  int firstInd = 0;
  for(int i=1;i<contents->getSize();i++) {
    if(endpoint.xpos > contents->get(i).xpos) {
      endpoint = contents->get(i);
      firstInd = i;
    }
    if(endpoint.xpos == contents->get(i).xpos && endpoint.ypos > contents->get(i).ypos) {
      firstInd = i;
      endpoint = contents->get(i);
    }
  }
  for(int i=0;i<4;i++) {
    cout << "Point " << i << ": ";
    contents->get(i).debug();
  }
  lastPoint = endpoint;
  cout << "got last and end point: ";
  lastPoint.debug();
  //hull->add(lastPoint);
  //contents->remove(firstInd);
  // Find the Leftmost point then add until found convex hull

  while((!lastPoint.equals(endpoint)||!hull->getSize()) && contents->getSize()) {
    cout << "In While Loop" << endl;
    int ind = 0;
    cout << "Hull Size Wh: " << hull->getSize() << endl;
    cout << "Contents Size: " << contents->getSize() << endl;
    //pointOnHull = contents->getSize()==verts->getSize() ? firstInd==0 ?
    //  contents->get(1) : contents->get(0) : contents->get(0);
    //pointOnHull = contents->get(0);
    //int i = contents->getSize()==verts->getSize() ? firstInd==0 ? 0 : 1 : 1;
    //for(;i<contents->getSize();i++) {
    for(int i=0;i<contents->getSize();i++) {
      //if(i != lastInd) {
        Edge* edgeOne = new Edge(pointOnHull,lastPoint);
        Edge* edgeTwo = new Edge(contents->get(i),lastPoint);
        if(edgeOne->determinant(edgeTwo) > 0) {
          ind = i;
          //lastInd = ind;
          pointOnHull = contents->get(i);
        }
        delete edgeOne;
        delete edgeTwo;
      //}
    }
    lastPoint = pointOnHull;
    hull->add(pointOnHull);
    contents->remove(ind);
  }
  for(int i=0;i<hull->getSize();i++) {
    cout << "Hull: " << i << " ";
    hull->get(i).debug();
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

void Face::addVert(Vertex* vert) {
  vert->getFaceIDs()->add(Integer(id));
  verts->add(vert);
}

void Face::addEdge(Edge* edge) {
  edge->getFaceIDs()->add(Integer(id));
  edges->add(edge);
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
