#include "face.h"

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

  findSeparatePaths(oneLoc,twoLoc,oneEdges,twoEdges);

  Array<Vertex*>* oneVerts = face->findVertsOnPath(oneEdges);
  Array<Vertex*>* twoVerts = face->findVertsOnPath(twoEdges);

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
    if(edge->get(i)->getFirst().xpos == oneLoc.xpos && edge->get(i)->getFirst().ypos == oneLoc.ypos) {
      if(!startOne) {
        startOne = edges->get(i);
      } else if(startOne != edge->get(i)) {
        startTwo = edges->get(i);
        i = edges->getSize();
      }
    }

    if(edge->get(i)->getSecond().xpos == oneLoc.xpos && edge->get(i)->getSecond().ypos == oneLoc.ypos) {
      if(!startOne) {
        startOne = edges->get(i);
      } else if(startOne != edge->get(i)) {
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
          tmp = startOne->getOtherPoint(startOne);
          i = edges->getSize();
        }
      if(edges->get(i)->getSecond().xpos == tmp.xpos && edges->get(i)->getSecond().ypos == tmp.ypos)
        if(edges->get(i) != startOne) {
          startOne = edges->get(i);
          one->add(startOne);
          tmp = startOne->getOtherPoint(startOne);
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
          tmp2 = startTwo->getOtherPoint(startTwo);
          i = edges->getSize();
        }
      if(edges->get(i)->getSecond().xpos == tmp2.xpos && edges->get(i)->getSecond().ypos == tmp2.ypos)
        if(edges->get(i) != startTwo) {
          startTwo = edges->get(i);
          two->add(startTwo);
          tmp = startTwo->getOtherPoint(startTwo);
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
