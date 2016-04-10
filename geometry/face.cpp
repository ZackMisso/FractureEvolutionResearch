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
  cout << "Start Separate" << endl;
  // create the list of new faces
  Array<Face*>* newFaces = new Array<Face*>();
  // get number of separations
  int numSeparations = 1;
  // create required data structures
  Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();
  Array<Vertex*>* oneVerts = new Array<Vertex*>();
  Array<Vertex*>* twoVerts = new Array<Vertex*>();
  // add new vert to both new adds
  oneVerts->add(newVert);
  twoVerts->add(newVert);
  // create data structures for new edge generation
  Array<Edge*>* newEdges = new Array<Edge*>();
  Vertex* newVertOne = 0x0;
  Vertex* newVertTwo = 0x0;
  Edge* edgeOne = 0x0;
  Edge* edgeTwo = 0x0;
  if(isConvex) {
    // convex case (easy)
    // choose two random edges
    int edgeIndOne = RNG::RandomInt(edges->getSize());
    int edgeIndTwo = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);
    edgeOne = edges->get(edgeIndOne);
    edgeTwo = edges->get(edgeIndTwo);
    // choose two random locations on those edges
    real edgeDistOne = RNG::RandomFloatMin(0.1);
    real edgeDistTwo = RNG::RandomFloatMin(0.1);
    // get the two points on the edges
    Point2 newPointOne = edgeOne->getPointBetween(edgeDistOne);
    Point2 newPointTwo = edgeTwo->getPointBetween(edgeDistTwo);
    // create the new verts
    newVertOne = new Vertex(newPointOne);
    newVertTwo = new Vertex(newPointTwo);
    newVertOne->setID(ids->incrementNextVert());
    newVertTwo->setID(ids->incrementNextVert());
    for(int i=0;i<edgeOne->getFaceIDs()->getSize();i++)
      newVertOne->getFaceIDs()->add(edgeOne->getFaceIDs()->get(i));
    for(int i=0;i<edgeTwo->getFaceIDs()->getSize();i++)
      newVertTwo->getFaceIDs()->add(edgeTwo->getFaceIDs()->get(i));
  } else {
    // concave case (harder)
    cout << "Concave Separate" << endl;
    // choose two random edges
    int edgeIndOne = RNG::RandomInt(edges->getSize());
    int edgeIndTwo = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);
    edgeOne = edges->get(edgeIndOne);
    edgeTwo = edges->get(edgeIndTwo);
    // choose two random locations on those edges
    real edgeDistOne = RNG::RandomFloatMinMax(0.1,0.9);
    real edgeDistTwo = RNG::RandomFloatMinMax(0.1,0.9);
    // get the two points on the edges
    Point2 newPointOne = edgeOne->getPointBetween(edgeDistOne);
    Point2 newPointTwo = edgeTwo->getPointBetween(edgeDistTwo);
    // create temporary edges to test intersection
    Edge* tmpEdgeOne = new Edge(newVert->getLocation().xpos,newVert->getLocation().ypos,newPointOne.xpos,newPointOne.ypos);
    Edge* tmpEdgeTwo = new Edge(newVert->getLocation().xpos,newVert->getLocation().ypos,newPointTwo.xpos,newPointTwo.ypos);
    // try to find intersectors
    Point2* utOne = new Point2();
    Point2* utTwo = new Point2();
    utOne->xpos = 0.0;
    utOne->ypos = 0.0;
    utTwo->xpos = 0.0;
    utTwo->ypos = 0.0;
    Edge* intersectorOne = tmpEdgeOne->intersects(edges,edgeOne,utOne);
    Edge* intersectorTwo = tmpEdgeTwo->intersects(edges,edgeTwo,utTwo);
    // react if there are intersectors
    if(intersectorOne) {
      newPointOne = intersectorOne->getIntersectionPoint(tmpEdgeOne);
      cout << "Intersector One" << endl;
      delete tmpEdgeOne;
      edgeOne = intersectorOne;
    }if(intersectorTwo) {
      newPointTwo = intersectorTwo->getIntersectionPoint(tmpEdgeTwo);
      cout << "Intersector Two" << endl;
      newPointTwo.debug();
      delete tmpEdgeTwo;
      edgeTwo = intersectorTwo;
    }
    // create the new verts
    newVertOne = new Vertex(newPointOne);
    newVertTwo = new Vertex(newPointTwo);
    newVertOne->setID(ids->incrementNextVert());
    newVertTwo->setID(ids->incrementNextVert());
    for(int i=0;i<edgeOne->getFaceIDs()->getSize();i++)
      newVertOne->getFaceIDs()->add(edgeOne->getFaceIDs()->get(i));
    for(int i=0;i<edgeTwo->getFaceIDs()->getSize();i++)
      newVertTwo->getFaceIDs()->add(edgeTwo->getFaceIDs()->get(i));
  }
  // split old edges
  Array<Edge*>* newEdgesTwo = new Array<Edge*>();
  Array<Edge*>* newEdgesOne = new Array<Edge*>();
  edgeOne->split(newEdgesOne,newVertOne->getLocation(),newVertOne->getID(),ids);
  // updated edges for Vert One
  for(int i=0;i<newEdgesOne->getSize();i++) {
    newEdges->add(newEdgesOne->get(i));
    newVertOne->getEdges()->add(newEdges->get(i));
  }
  // check to make sure the secound edge isn't the same
  if(edgeOne == edgeTwo) {
    for(int i=0;i<newEdges->getSize();i++)
      if(newEdges->get(i)->isOn(newVertTwo->getLocation())) {
        edgeTwo = newEdges->remove(i);
        newEdgesOne->remove(i);
        i = newEdges->getSize();
      }
  }
  edgeTwo->split(newEdgesTwo,newVertTwo->getLocation(),newVertTwo->getID(),ids);
  // updated edges for Vert Two
  for(int i=0;i<newEdgesTwo->getSize();i++) {
    newVertTwo->getEdges()->add(newEdgesTwo->get(i));
    newEdges->add(newEdgesTwo->get(i));
  }
  // remove old edges
  edges->remove(edgeOne);
  edges->remove(edgeTwo);
  // remove edges from the verts they are connected to
  Array<Vertex*>* vertsRemOne = getVertsInEdge(edgeOne);
  Array<Vertex*>* vertsRemTwo = getVertsInEdge(edgeTwo);
  for(int i=0;i<vertsRemOne->getSize();i++) {
    Vertex* v = vertsRemOne->get(i);
    for(int j=0;j<v->getEdges()->getSize();j++)
      if(v->getEdges()->get(j)->getID() == edgeOne->getID()) {
        v->getEdges()->remove(j);
        j = v->getEdges()->getSize();
        for(int k=0;k<newEdgesOne->getSize();k++)
          if(newEdgesOne->get(k)->eitherMatch(v->getID())) {
            v->getEdges()->add(newEdgesOne->get(k));
            k = newEdgesOne->getSize();
          }
      }
  }
  for(int i=0;i<vertsRemTwo->getSize();i++) {
    Vertex* v = vertsRemTwo->get(i);
    for(int j=0;j<v->getEdges()->getSize();j++)
      if(v->getEdges()->get(j)->getID() == edgeTwo->getID()) {
        v->getEdges()->remove(j);
        j = v->getEdges()->getSize();
        for(int k=0;k<newEdgesTwo->getSize();k++)
          if(newEdgesTwo->get(k)->eitherMatch(v->getID())) {
            v->getEdges()->add(newEdgesTwo->get(k));
            k = newEdgesTwo->getSize();
          }
      }
  }
  newEdgesOne->clear();
  newEdgesTwo->clear();
  vertsRemOne->clear();
  vertsRemTwo->clear();
  delete newEdgesOne;
  delete newEdgesTwo;
  delete vertsRemOne;
  delete vertsRemTwo;
  delete edgeOne;
  delete edgeTwo;
  // create new edges that will be separating
  Edge* separateEdgeOne = new Edge(newVertOne->getLocation(),newVert->getLocation(),newVertOne->getID(),newVert->getID());
  Edge* separateEdgeTwo = new Edge(newVert->getLocation(),newVertTwo->getLocation(),newVert->getID(),newVertTwo->getID());
  newVertOne->getEdges()->add(separateEdgeOne);
  newVertTwo->getEdges()->add(separateEdgeTwo);
  newVert->getEdges()->add(separateEdgeOne);
  newVert->getEdges()->add(separateEdgeTwo);
  separateEdgeOne->setID(ids->incrementNextEdge());
  separateEdgeTwo->setID(ids->incrementNextEdge());
  // add new edges to face
  while(newEdges->getSize())
    edges->add(newEdges->removeLast());
  delete newEdges;
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
  while(next.xpos != start.xpos || next.ypos != start.ypos) {
    sortedPoints->add(current);
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

Array<Vertex*>* Face::getVertsInEdge(Edge* edge) {
  Array<Vertex*>* vertsInEdge = new Array<Vertex*>();
  int idOne = edge->getFirstVertID();
  int idTwo = edge->getSecondVertID();
  for(int i=0;i<verts->getSize();i++) {
    if(verts->get(i)->getID() == idOne)
      vertsInEdge->add(verts->get(i));
    if(verts->get(i)->getID() == idTwo)
      vertsInEdge->add(verts->get(i));
  }
  return vertsInEdge;
}

// THIS BECOMES AN ISSUE WHEN SPLITTING A POLYGON WITH HOLES
// Triangulation by Ear Clipping
void Face::splitIntoTrimeshConcave() { // REWRITE
  clearTrimesh();
  Array<Point2>* points = sortPointsByPath();
  if(isClockwise(points))
    points = reversePath(points);
  cout << "Writing Points" << endl;
  for(int i=0;i<points->getSize();i++)
    DebugController::writePointState(points->get(i));
  cout << "Finished Writing Points" << endl;
  while(points->getSize()>3) {
    //cout << "While:: " << points->getSize() << endl;
    //cout << "Face ID: " << id << endl;
    for(int i=0;i<points->getSize();i++) {
      // get next and previous point
      int prev = i==0 ? points->getSize()-1 : i-1;
      int next = i==points->getSize()-1 ? 0 : i+1;
      //cout << "Cur: " << i << " Nex: " << next << " Prev: " << prev << endl;
      // create two edges going from current point
      Edge* one = new Edge(points->get(i),points->get(next));
      Edge* two = new Edge(points->get(i),points->get(prev));
      // get their interiorAngle
      real interiorAngle = one->interiorAngle(two);
      //cout << "Int Angle: " << interiorAngle << endl;
      // make sure it is not a reflex angle.
      if(interiorAngle < PI) {
        // create the triangle
        Tri* tri = new Tri(points->get(prev),points->get(i),points->get(next));
        bool isEar = true;
        for(int j=0;j<points->getSize();j++) {
          if(j != i && j != prev && j != next) {
            // test if the triangle is valid by making sure no verts are within it
            points->get(j).debug();
            if(tri->isInside(points->get(j))) {
              isEar = false;
              j = points->getSize();
            }
          }
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

// NOT WORKING
bool Face::isClockwise(Array<Point2>* sortedPath) {
  float sum = 0.0f;
  for(int i=1;i<sortedPath->getSize();i++)
    sum += (sortedPath->get(i).xpos-sortedPath->get(i-1).xpos) *
      (sortedPath->get(i).ypos + sortedPath->get(i-1).ypos);
  sum += (sortedPath->get(0).xpos-sortedPath->get(sortedPath->getSize()-1).xpos) *
    (sortedPath->get(0).ypos + sortedPath->get(sortedPath->getSize()-1).ypos);
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

real Face::cross(const Point2& o,const Point2& a,const Point2& b) {
  return (a.xpos-o.xpos)*(b.ypos-o.ypos)-(a.ypos-o.ypos)*(b.xpos-o.xpos);
}

// Andrew's monotone chain 2D convex hull Algorithm
// code is a modified version of what was provided here ::
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
Array<Point2>* Face::getConvexHull() {
  int n = verts->getSize();
  int k = 0;
  vector<Point2> hull(2*n);
  vector<Point2> tmpVerts(n);
  for(int i=0;i<verts->getSize();i++) {
    tmpVerts[i] = verts->get(i)->getLocation();
    verts->get(i)->getLocation().debug();
  }
  for(int i=0;i<tmpVerts.size();i++)
    tmpVerts[i].debug();
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

void Face::clear() {
  verts->clear();
  edges->clear();
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
