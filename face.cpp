#include "face.h"
#include "rng.h"

#include <cstdlib>

#include <iostream>

using namespace std;

Face::Face() {
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
}

Face::Face(Array<Vertex*>* verts) {
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  // initialize arrays
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
  cout << "Intersections :: " << intersections << endl;
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
  cout << "Beginning Separation" << endl;
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

  cout << "Initialized Everything" << endl;

  for(int i=0;i<2;i++) {
    cout << "Starting Face" << endl;
    int edgeInd = RNG::RandomInt(edges->getSize());
    float edgeDist = RNG::RandomFloat();
    Edge* edge = edges->get(edgeInd);
    cout << "Calculating Point Between" << endl;
    Point2 newPoint = edge->getPointBetween(edgeDist);
    cout << "Creating new Edge" << endl;
    Edge* newEdge = new Edge(x,y,newPoint.xpos,newPoint.ypos);
    // THIS IS INEFFICIENT... WILL HAVE TO FIX LATER
    cout << "Checking Intersections" << endl;
    for(int j=0;j<edges->getSize();j++)
      if(edges->get(j)!=edge)
        if(edges->get(i)->intersects(newEdge)) {
          // fix the newEdge's second location
          // TODO :: LATER
        }
    cout << "Setting Point Location" << endl;
    if(i) {
      oneLoc.xpos = newPoint.xpos;
      oneLoc.ypos = newPoint.ypos;
    } else {
      twoLoc.xpos = newPoint.xpos;
      twoLoc.ypos = newPoint.ypos;
    }
    cout << "Creating New Vertex" << endl;
    Vertex* newVert = new Vertex(newPoint);
    oneVerts->add(newVert);
    twoVerts->add(newVert);

    oneEdges->add(newEdge);
    twoEdges->add(newEdge);

    numSeperations--;
  }
  // update faces
  cout << "Calculating The Separate Paths" << endl;
  findSeparatePaths(oneEdges,twoEdges,oneLoc,twoLoc);
  cout << "Finding The Verts on the First Path" << endl;
  Array<Vertex*>* tmpOne = findVertsOnPath(oneEdges);
  cout << "finding The Verts on the Second Path" << endl;
  Array<Vertex*>* tmpTwo = findVertsOnPath(twoEdges);
  cout << "Cleaning Up" << endl;
  while(tmpOne->getSize())
    oneVerts->add(tmpOne->removeLast());
  while(tmpTwo->getSize())
    twoVerts->add(tmpTwo->removeLast());
  delete tmpOne;
  delete tmpTwo;
  cout << "Creating First Face" << endl;
  Face* oneFace = new Face();
  oneFace->setVerts(oneVerts);
  oneFace->setEdges(oneEdges);
  cout << "Creating Second Face" << endl;
  Face* twoFace = new Face();
  twoFace->setVerts(twoVerts);
  twoFace->setEdges(twoEdges);
  cout << "Adding Faces" << endl;
  newFaces->add(oneFace);
  newFaces->add(twoFace);

  // do the remaining separations
  while(numSeperations) {
    // to be implemented
    numSeperations--;
  }
  cout << "Exiting Separation" << endl;
  return newFaces;
}

// this may also need different forms of implementations
Array<Face*>* Face::separate(Point2 newPoint) {
  // to be implemented
  return 0x0;
}

Array<Face*>* Face::separate(Point2 start,Point2 end) {
  // to be implemented
  return 0x0;
}

void Face::findSeparatePaths(Array<Edge*>* one,Array<Edge*>* two,Point2 oneLoc,Point2 twoLoc) {
  Edge* startOne = 0x0;
  Edge* startTwo = 0x0;
  for(int i=0;i<edges->getSize();i++) {
    if(edges->get(i)->getFirst().xpos == oneLoc.xpos && edges->get(i)->getFirst().ypos == oneLoc.ypos) {
      if(!startOne) {
        startOne = edges->get(i);
      } else if(startOne != edges->get(i)) {
        startTwo = edges->get(i);
        i = edges->getSize();
      }
    }

    if(edges->get(i)->getSecond().xpos == oneLoc.xpos && edges->get(i)->getSecond().ypos == oneLoc.ypos) {
      if(!startOne) {
        startOne = edges->get(i);
      } else if(startOne != edges->get(i)) {
        startTwo = edges->get(i);
        i = edges->getSize();
      }
    }
  }

  // Follow edges until you reach the final point
  Point2 tmp = startOne->getOtherPoint(oneLoc);
  Point2 tmp2 = startTwo->getOtherPoint(oneLoc);

  one->add(startOne);
  two->add(startTwo);

  while(tmp.xpos != twoLoc.xpos && tmp.ypos != twoLoc.ypos) {
    for(int i=0;i<edges->getSize();i++) {
      if(edges->get(i)->getFirst().xpos == tmp.xpos && edges->get(i)->getFirst().ypos == tmp.ypos)
        if(edges->get(i) != startOne) {
          startOne = edges->get(i);
          one->add(startOne);
          tmp = startOne->getOtherPoint(tmp);
          i = edges->getSize();
        }
      if(edges->get(i)->getSecond().xpos == tmp.xpos && edges->get(i)->getSecond().ypos == tmp.ypos)
        if(edges->get(i) != startOne) {
          startOne = edges->get(i);
          one->add(startOne);
          tmp = startOne->getOtherPoint(tmp);
          i = edges->getSize();
        }
    }
  }

  while(tmp2.xpos != twoLoc.xpos && tmp2.ypos != twoLoc.ypos) {
    for(int i=0;i<edges->getSize();i++) {
      if(edges->get(i)->getFirst().xpos == tmp2.xpos && edges->get(i)->getFirst().ypos == tmp2.ypos)
        if(edges->get(i) != startTwo) {
          startTwo = edges->get(i);
          two->add(startTwo);
          tmp2 = startTwo->getOtherPoint(tmp2);
          i = edges->getSize();
        }
      if(edges->get(i)->getSecond().xpos == tmp2.xpos && edges->get(i)->getSecond().ypos == tmp2.ypos)
        if(edges->get(i) != startTwo) {
          startTwo = edges->get(i);
          two->add(startTwo);
          tmp = startTwo->getOtherPoint(tmp2);
          i = edges->getSize();
        }
    }
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

void Face::setVerts(Array<Vertex*>* param) { verts = param; }
void Face::setEdges(Array<Edge*>* param) { edges = param; }
