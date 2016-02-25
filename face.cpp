#include "face.h"
#include "rng.h"
#include "debug.h"
#include "debugController.h"

#include <cstdlib>

#include <iostream>

using namespace std;

Face::Face() {
  verts = new Array<Vertex*>();
  edges = new Array<Edge*>();
  id = DebugController::getNextFace();
  selected = false;
}

Face::Face(Array<Vertex*>* verts) {
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
  //cout << "Intersections :: " << intersections << endl;
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
  //cout << "Beginning Separation" << endl;
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

  //cout << "Initialized Everything" << endl;

  int edgeIndOne = -1;

  Array<Edge*>* tmpEdges = new Array<Edge*>();
  Array<Edge*>* edgesToRemove = new Array<Edge*>();

  for(int i=0;i<2;i++) {
    //cout << "Starting Face" << endl;
    int edgeInd;
    if(edgeIndOne==-1) {
      edgeInd = RNG::RandomInt(edges->getSize());
      edgeIndOne = edgeInd;
    } else
      edgeInd = RNG::RandomIntWithException(edges->getSize(),edgeIndOne);

    float edgeDist = RNG::RandomFloat();
    Edge* edge = edges->get(edgeInd);
    //cout << "Calculating Point Between" << endl;
    Point2 newPoint = edge->getPointBetween(edgeDist);
    //edge->split(tmpEdges,newPoint);
    //cout << "Creating new Edge" << endl;
    Edge* newEdge = new Edge(x,y,newPoint.xpos,newPoint.ypos);
    //cout << "Finding Intersector" << endl;
    Edge* intersector = newEdge->intersects(edges,edge);
    if(intersector){
      //cout << "Found Intersector" << endl;
      //Debug::printPoint(newPoint);
      newPoint = intersector->getIntersectionPoint(newEdge);
      //Debug::printPoint(newPoint);
      //Debug::printPoint(newPoint);
      //Debug::printLine(intersector);
      //cout << "Testing New Edge" <<endl;
      //Debug::printLine(newEdge);
      delete newEdge;
      newEdge = new Edge(x,y,newPoint.xpos,newPoint.ypos);
      //newEdge->getSecond().setXpos(newPoint.xpos);
      //newEdge->getSecond().setYpos(newPoint.ypos);
      //Debug::printLine(newEdge);
      edge = intersector;
    }else{
      //cout << "No Intersector Found" << endl;
    }
    edge->split(tmpEdges,newPoint);
    //Debug::printLines(tmpEdges);

    //cout << "OLD EDGE :: ";
    //edge->debug();
    //cout << "NEW EDGE :: " << x << " " << y << " " << newPoint.xpos << " "<< newPoint.ypos << endl;
    // THIS IS INEFFICIENT... WILL HAVE TO FIX LATER
    //cout << "Checking Intersections" << endl;
    //for(int j=0;j<edges->getSize();j++)
    //  if(edges->get(j)!=edge)
    //    if(edges->get(i)->intersects(newEdge)) {
    //      // fix the newEdge's second location
    //      // TODO :: LATER
    //    }
    //cout << "Setting Point Location" << endl;
    if(i) {
      oneLoc.xpos = newPoint.xpos;
      oneLoc.ypos = newPoint.ypos;
    } else {
      twoLoc.xpos = newPoint.xpos;
      twoLoc.ypos = newPoint.ypos;
    }
    //cout << "Creating New Vertex" << endl;
    Vertex* newVert = new Vertex(newPoint);
    oneVerts->add(newVert);
    twoVerts->add(newVert);
    //verts->add(newVert);

    oneEdges->add(newEdge);
    twoEdges->add(newEdge);
    edgesToRemove->add(edge);

    numSeperations--;
  }
  while(tmpEdges->getSize())
    edges->add(tmpEdges->removeLast());
  while(edgesToRemove->getSize())
    edges->remove(edgesToRemove->removeLast());
  delete edgesToRemove;
  delete tmpEdges;
  //Debug::printLines(edges);
  // update faces
  //cout << "Calculating The Separate Paths" << endl;
  findSeparatePaths(oneEdges,twoEdges,oneLoc,twoLoc);
  //cout << "OneLoc :: " << oneLoc.xpos << " :: " << oneLoc.ypos << endl;
  //cout << "TwoLoc :: " << twoLoc.xpos << " :: " << twoLoc.ypos << endl;
  //cout << "One Edges :: " << endl;
  //Debug::printLines(oneEdges);
  //cout << "Two Edges :: " << endl;
  //Debug::printLines(twoEdges);
  //cout << "Finding The Verts on the First Path" << endl;
  Array<Vertex*>* tmpOne = findVertsOnPath(oneEdges);
  //Debug::printPoints(tmpOne);
  //cout << "finding The Verts on the Second Path" << endl;
  Array<Vertex*>* tmpTwo = findVertsOnPath(twoEdges);
  //cout << "Cleaning Up" << endl;
  while(tmpOne->getSize())
    oneVerts->add(tmpOne->removeLast());
  while(tmpTwo->getSize())
    twoVerts->add(tmpTwo->removeLast());
  //cout << "First Verts :: " << endl;
  //Debug::printPoints(oneVerts);
  //cout << "Second Verts :: " << endl;
  //Debug::printPoints(twoVerts);
  delete tmpOne;
  delete tmpTwo;
  //cout << "Creating First Face" << endl;
  Face* oneFace = new Face();
  oneFace->setVerts(oneVerts);
  oneFace->setEdges(oneEdges);
  //cout << "Creating Second Face" << endl;
  Face* twoFace = new Face();
  twoFace->setVerts(twoVerts);
  twoFace->setEdges(twoEdges);
  //cout << "Adding Faces" << endl;
  newFaces->add(oneFace);
  newFaces->add(twoFace);

  // do the remaining separations
  while(numSeperations) {
    // to be implemented
    numSeperations--;
  }
  //cout << "Exiting Separation" << endl;
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
  //cout << "Starting Separate Paths" << endl;
  Edge* startOne = 0x0;
  Edge* startTwo = 0x0;
  Edge* errorFinder = 0x0;
  //cout << "OneLoc :: " << oneLoc.xpos << " :: " << oneLoc.ypos << endl;
  //cout << "TwoLoc :: " << twoLoc.xpos << " :: " << twoLoc.ypos << endl;
  //Debug::printLines(edges);
  //startOne->getFirst();
  Array<Edge*>* tmpArray = new Array<Edge*>();
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)->eitherMatch(oneLoc))
      tmpArray->add(edges->get(i));
  //cout << "Size Of Edges :: " << tmpArray->getSize() << endl;
  //Debug::printLines(tmpArray);
  Edge* on = tmpArray->get(0);
  Point2 poi = on->getOtherPoint(oneLoc);
  one->add(on);
  //cout << "POI :: " << poi.xpos << " " << poi.ypos << endl;
  Point2 prev = oneLoc;
  while(poi.xpos != twoLoc.xpos || poi.ypos != twoLoc.ypos) {
    //cout << "THIS IS RUNNING" << endl;
    //cout << "POI :: " << poi.xpos << " " << poi.ypos << endl;
    Edge* tmpe = 0x0;
    for(int i=0;i<edges->getSize();i++)
      if(edges->get(i)->eitherMatch(poi) && !edges->get(i)->eitherMatch(prev))
        tmpe = edges->get(i);
      //tmpe->debug();
    one->add(tmpe);
    prev.xpos = poi.xpos;
    prev.ypos = poi.ypos;
    poi = tmpe->getOtherPoint(poi);
  }

  on = tmpArray->get(1);
  poi = on->getOtherPoint(oneLoc);
  two->add(on);
  prev = oneLoc;
  //cout << "POI :: " << poi.xpos << " " << poi.ypos << endl;
  while(poi.xpos != twoLoc.xpos || poi.ypos != twoLoc.ypos) {
    //cout << "POI :: " << poi.xpos << " " << poi.ypos << endl;
    //Point2 prev = oneLoc;
    Edge* tmpe = 0x0;
    for(int i=0;i<edges->getSize();i++)
      if(edges->get(i)->eitherMatch(poi) && !edges->get(i)->eitherMatch(prev))
        tmpe = edges->get(i);
      //tmpe->debug();
    two->add(tmpe);
    prev.xpos = poi.xpos;
    prev.ypos = poi.ypos;
    poi = tmpe->getOtherPoint(poi);
  }


  //cout << "Printing One :: " << endl;
  //Debug::printLines(one);
  //cout << "Printing Two :: " << endl;
  //Debug::printLines(two);

  //errorFinder->getFirst();






  /*for(int i=0;i<edges->getSize();i++) {
    cout << "Enter For Loop for Separate Paths" << endl;
    if(edges->get(i)->getFirst().xpos == oneLoc.xpos && edges->get(i)->getFirst().ypos == oneLoc.ypos) {
      cout << "TIS A MATCH" << endl;
      if(!startOne) {
        cout << "Found First Edge in First" << endl;
        startOne = edges->get(i);
      } else if(startOne != edges->get(i)) {
        cout << "Found Second Edge in First" << endl;
        startTwo = edges->get(i);
        i = edges->getSize();
      }
    }

    if(edges->get(i)->getSecond().xpos == oneLoc.xpos && edges->get(i)->getSecond().ypos == oneLoc.ypos) {
      cout << "TIS A MATCH TOO" << endl;
      if(!startOne) {
        cout << "Found First Edge in Second" << endl;
        startOne = edges->get(i);
      } else if(startOne != edges->get(i)) {
        cout << "Found Second Edge in Second" << endl;
        startTwo = edges->get(i);
        i = edges->getSize();
      }
    }
  }

  cout << "Getting Other Points" << endl;

  if(!one)
    cout << "First Array Not Initialized" << endl;
  if(!two)
    cout << "Second Array Not Initialized" << endl;
  if(!startOne)
    cout << "First Edge Not Initialized" << endl;
  if(!startTwo)
    cout << "Second Edge Not Initialized" << endl;

  // Follow edges until you reach the final point
  Point2 tmp = startOne->getOtherPoint(oneLoc);
  Point2 tmp2 = startTwo->getOtherPoint(oneLoc);

  one->add(startOne);
  two->add(startTwo);

  cout << "Start One :: ";
  startOne->debug();

  cout << "Start Two :: ";
  startTwo->debug();

  cout << "Entering Traversal Loop" << endl;
  cout << tmp.xpos << " " << tmp.ypos << endl;
  //cout << tmp.xpos != twoLoc.xpos << endl;
  cout << "Blah" << endl;
  while(tmp.xpos != twoLoc.xpos && tmp.ypos != twoLoc.ypos) {
    cout << "Traversing" << endl;
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
    cout << "Traversing Too" << endl;
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
  }*/

}

Array<Vertex*>* Face::findVertsOnPath(Array<Edge*>* edgs) {
  // this should be fixed so that it only needs to check the first one's location
  Array<Vertex*>* vp = new Array<Vertex*>();
  //cout << "In find Verts" << endl;
  //for(int i=0;i<edgs->getSize();i++) {
  //  for(int j=0;j<verts->getSize();j++)
  //    if(isMatch())
  //}


  for(int i=0;i<edgs->getSize();i++)
    for(int j=0;j<verts->getSize();j++) {
      //cout << "First Check" << endl;
      if(edgs->get(i)->getFirst().xpos == verts->get(j)->getLocation().xpos && edgs->get(i)->getFirst().ypos == verts->get(j)->getLocation().ypos)
        //cout << "Calling Contains" << endl;
        if(!vp->contains(verts->get(j))){
          vp->add(verts->get(j));
          j = verts->getSize();
        }
        //cout << "Outside Contains" << endl;

      //cout << "Second Check" << endl;
      if(j!=verts->getSize())
        if(edgs->get(i)->getSecond().xpos == verts->get(j)->getLocation().xpos && edgs->get(i)->getSecond().ypos == verts->get(j)->getLocation().ypos)
          //cout << "Calling Contains" << endl;
          if(!vp->contains(verts->get(j))){
            vp->add(verts->get(j));
            j = verts->getSize();
          }
          //cout << "Outside Contains" << endl;
    }
  return vp;
}

Array<Vertex*>* Face::getVerts() { return verts; }
Array<Edge*>* Face::getEdges() { return edges; }
int Face::getID() { return id; }
bool Face::getSelected() { return selected; }

void Face::setVerts(Array<Vertex*>* param) { verts = param; }
void Face::setEdges(Array<Edge*>* param) { edges = param; }
void Face::setID(int param) { id = param; }
void Face::setSelected(bool param) { selected = param; }
