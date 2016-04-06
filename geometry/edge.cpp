#include "edge.h"
#include "../test/debug.h"
#include "../test/debugController.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

Edge::Edge(Point2 one,Point2 two) {
  faceIDs = new Array<Integer>();
  first.xpos = one.xpos;
  first.ypos = one.ypos;
  second.xpos = two.xpos;
  second.ypos = two.ypos;
  firstVertID = -1;
  secondVertID = -1;
  id = -1;
  selected = false;
  isBoundary = false;
}

Edge::Edge(Point2 one,Point2 two,int idone,int idtwo) {
  faceIDs = new Array<Integer>();
  first.xpos = one.xpos;
  first.ypos = one.ypos;
  second.xpos = two.xpos;
  second.ypos = two.ypos;
  firstVertID = idone;
  secondVertID = idtwo;
  id = -1;
  selected = false;
  isBoundary = false;
}

Edge::Edge(real x,real y,real xx,real yy) {
  faceIDs = new Array<Integer>();
  first.xpos = x;
  first.ypos = y;
  second.xpos = xx;
  second.ypos = yy;
  firstVertID = -1;
  secondVertID = -1;
  id = -1;
  selected = false;
  isBoundary = false;
}

Edge::Edge(real x,real y,real xx,real yy,int idone,int idtwo) {
  faceIDs = new Array<Integer>();
  first.xpos = x;
  first.ypos = y;
  second.xpos = xx;
  second.ypos = yy;
  firstVertID = idone;
  secondVertID = idtwo;
  id = -1;
  selected = false;
  isBoundary = false;
}

Edge* Edge::copy() {
  Edge* edge = new Edge(first,second,firstVertID,secondVertID);
  edge->setSelected(selected);
  edge->setIsBoundary(isBoundary);
  edge->setID(id);
  for(int i=0;i<faceIDs->getSize();i++)
    edge->getFaceIDs()->add(faceIDs->get(i));
  return edge;
}

void Edge::draw() {
	glVertex2f(first.xpos,first.ypos);
  glVertex2f(second.xpos,second.ypos);
}

bool Edge::intersects(Edge* other) {
  Point2 p = first;
  Point2 q = other->getFirst();
  Point2 r = second.minus(first);
  Point2 s = other->getSecond().minus(other->getFirst());
  Point2 sub = q.minus(p);
  real rcs = r.wedgeProduct(s);
  real tnum = sub.wedgeProduct(s);
  real unum = sub.wedgeProduct(r);
  // first case
  if(rcs == 0.0 && unum == 0.0) {
    // colinier case .. don't need to worry about I think
    return false;
  }
  // second case
  if(rcs == 0.0 && unum != 0.0) {
    // parallel and non-intersecting
    return false;
  }
  // third case
  real t = tnum / rcs;
  real u = unum / rcs;
  if(rcs != 0.0 && t < 1.0 && t > 0.0 && u < 1.0 && u > 0.0) {
    // points meet at ::
    // p + t*r
    // q + u*s
    return true;
  }
  // fourth case
  // not parallel and do not intersect
  return false;
}

bool Edge::intersects(Edge* other,Point2* ut) {
  Point2 p = first;
  Point2 q = other->getFirst();
  Point2 r = second.minus(first);
  Point2 s = other->getSecond().minus(other->getFirst());
  Point2 sub = q.minus(p);
  real rcs = r.wedgeProduct(s);
  real tnum = sub.wedgeProduct(s);
  real unum = sub.wedgeProduct(r);
  // first case
  if(rcs == 0.0 && unum == 0.0) {
    // colinier case .. don't need to worry about I think
    return false;
  }
  // second case
  if(rcs == 0.0 && unum != 0.0) {
    // parallel and non-intersecting
    return false;
  }
  // third case
  real t = tnum / rcs;
  real u = unum / rcs;
  if(rcs == 0.0 && t < 1.0 && t > 0.0 && u < 1.0 && u > 0.0) {
    // points meet at ::
    // p + t*r
    // q + u*s
    ut->xpos = t;
    ut->ypos = u;
    return true;
  }
  // fourth case
  // not parallel and do not intersect
  return false;
}

bool Edge::intersectsOld(Edge* other) {
  //cout << "////////////////////////////////////////" << endl;
  Point2 oFirst = other->getFirst();
  Point2 oSecond = other->getSecond();

  //cout << "TWO :: " << oFirst.xpos << " " << oFirst.ypos << " " << oSecond.xpos << " " << oSecond.ypos << endl;
  //cout << "ONE :: " << first.xpos << " " << first.ypos << " " << second.xpos << " " << second.ypos << endl;

  real s1x = first.xpos - second.xpos;
  real s1y = first.ypos - second.ypos;
  real s2x = oFirst.xpos - oSecond.xpos;
  real s2y = oFirst.ypos - oSecond.ypos;

  //cout << "S1X :: " << s1x << endl;
  //cout << "S2X :: " << s2x << endl;
  //cout << "S1Y :: " << s1y << endl;
  //cout << "S2Y :: " << s2y << endl;

  real det = -s2x * s1y + s1x * s2y;

  //if(det<0)
  //  det*=-1;

  //cout << "Det :: " << det << endl;

  if(det == 0.0f)
    return false;

  real tmp1 = (first.xpos - oFirst.xpos);
  real tmp2 = (first.ypos - oFirst.ypos);

  real s = (-s1y * tmp1 + s1x * tmp2) / det;
  real t = (-s2y * tmp1 + s2x * tmp2) / det;

  //if(s<0)
  //  s*=-1;
  //if(t<0)
  //  t*=-1;

  //cout << "S :: " << s << endl;
  //cout << "T :: " << t << endl;

  //cout << "////////////////////////////////////////" << endl;

  if(s < 0 && s > -1 && t < 0 && t > -1)
    return true;



  return false;
}

Edge* Edge::intersects(Array<Edge*>* edges,Edge* ignore) {
  for(int i=0;i<edges->getSize();i++)
    if(edges->get(i)!=ignore)
      //cout << "Calling Intersects" << endl;
      if(intersects(edges->get(i)))
        return edges->get(i);
  return 0x0;
}

Point2 Edge::getIntersectionPoint(Edge* other) {
  //cout << "//////////////////////////////////" << endl;
  //cout << "This Edge :: " << endl;
  //Debug::printLine(this);
  //cout << "Other Edge :: " << endl;
  //Debug::printLine(other);
  Point2 intersection;
  intersection.xpos = -1;
  intersection.ypos = -1;
  Point2 oFirst = other->getFirst();
  Point2 oSecond = other->getSecond();
  real s1x = first.xpos - second.xpos;
  real s1y = first.ypos - second.ypos;
  real s2x = oFirst.xpos - oSecond.xpos;
  real s2y = oFirst.ypos - oSecond.ypos;
  real det = -s2x * s1y + s1x * s2y;
  real tmp1 = (first.xpos - oFirst.xpos);
  real tmp2 = (first.ypos - oFirst.ypos);
  real s = (-s1y * tmp1 + s1x * tmp2) / det;
  real t = (-s2y * tmp1 + s2x * tmp2) / det;
  s*=-1;
  t*=-1;
  //cout << "s1x :: " << s1x << endl;
  //cout << "s1y :: " << s1y << endl;
  //cout << "s2x :: " << s2x << endl;
  //cout << "s2y :: " << s2y << endl;
  //cout << "T :: " << t << endl;
  //cout << "S :: " << s << endl;
  //cout << "Xpos :: " << first.xpos << endl;
  //cout << "Ypos :: " << first.ypos << endl;
  intersection.xpos = first.xpos - t * s1x;
  intersection.ypos = first.ypos - t * s1y;
  //cout << "INTERSECTION :: " << endl;
  //Debug::printPoint(intersection);
  //cout << "///////////////!!!///////////////////" << endl;
  return intersection;
}

bool Edge::eitherMatch(Point2 point) {
  if(first.xpos == point.xpos && first.ypos == point.ypos)
    return true;
  if(second.xpos == point.xpos && second.ypos == point.ypos)
    return true;
  return false;
}

bool Edge::eitherMatch(int pointID) {
  if(firstVertID == pointID)
    return true;
  if(secondVertID == pointID)
    return true;
  return false;
}

Point2 Edge::getOtherPoint(Point2 point) {
  if(point.xpos == first.xpos && point.ypos == first.ypos)
    return second;
  return first;
}

Point2 Edge::getOtherPoint(int pointID) {
  if(firstVertID == pointID)
    return first;
  return second;
}

Point2 Edge::getPointBetween(real linePos) {
  Point2 newPoint;
  newPoint.xpos = ((second.xpos-first.xpos) * linePos) + first.xpos;
  newPoint.ypos = ((second.ypos-first.ypos) * linePos) + first.ypos;
  return newPoint;
}

void Edge::splitOld(Array<Edge*>* cb,Point2 point) {
  Edge* one = new Edge(first,point);
  Edge* two = new Edge(point,second);
  DebugController::writeCreateEdge(one);
  DebugController::writeCreateEdge(two);
  cb->add(one);
  cb->add(two);
}

void Edge::split(Array<Edge*>* cb,Point2 point,int pointID,IDTracker* ids) {
  Edge* one = new Edge(first,point,firstVertID,pointID);
  Edge* two = new Edge(point,second,pointID,secondVertID);
  one->setID(ids->incrementNextEdge());
  two->setID(ids->incrementNextEdge());
  for(int i=0;i<faceIDs->getSize();i++) {
    one->getFaceIDs()->add(faceIDs->get(i));
    two->getFaceIDs()->add(faceIDs->get(i));
  }
  one->setIsBoundary(isBoundary);
  two->setIsBoundary(isBoundary);
  cb->add(one);
  cb->add(two);
}

real Edge::determinant(Edge* other) {
  real xOne = second.xpos - first.xpos;
  real yOne = second.ypos - first.ypos;
  real xTwo = other->getSecond().xpos - other->getFirst().xpos;
  real yTwo = other->getSecond().ypos - other->getFirst().ypos;
  return xOne*yTwo - yOne*xTwo;
}

real Edge::length() {
  real dx = second.xpos - first.xpos;
  real dy = second.ypos - first.ypos;
  return sqrt(dx*dx + dy*dy);
}

real Edge::dot(Edge* other) {
  real dxOne = second.xpos - first.xpos;
  real dyOne = second.ypos - first.ypos;
  real dxTwo = getSecond().xpos - getFirst().xpos;
  real dyTwo = getSecond().ypos - getFirst().ypos;
  return dxOne*dxTwo + dyOne*dyTwo;
}

// Minus for anti-clockwise, plus for clockwise
real Edge::interiorAngle(Edge* other) {
  return PI + atan2(determinant(other),dot(other));
}

//bool Edge::isOn(Edge* other) { // THIS NEEDS TO BE TESTED
//  float dxOne = second.xpos - first.xpos;
//  float dyOne = second.ypos - first.ypos;
//  float dxTwo = other->getSecond().xpos - other->getFirst().xpos;
//  float dyTwo = other->getSecond().ypos - other->getSecond().ypos;
//  bool vert = dxOne==0 && dxTwo==0;
//  if(!vert && (dxOne==0 || dxTwo==0))
//    return false;
//  float slOne = dyOne/dxOne;
//  float slTwo = dyTwo/dxTwo;
//  if(slOne==-slTwo)
//    slOne*=-1;
//  if(vert || slOne == slTwo || slOne == -slTwo) {
//    float bOne = second.ypos - second.xpos * slOne;
//    float bTwo = other->getSecond().ypos - other->getSecond().xpos * slTwo;
//    if(bOne == bTwo)
//      return true;
//  }
//  return false;
//}

void Edge::setFirst(Point2 point) {
  first.xpos = point.xpos;
  first.ypos = point.ypos;
}

void Edge::setSecond(Point2 point) {
  second.xpos = point.xpos;
  second.ypos = point.ypos;
}

Array<Integer>* Edge::getFaceIDs() { return faceIDs; }
Point2 Edge::getFirst() { return first; }
Point2 Edge::getSecond() { return second; }
int Edge::getID() { return id; }
int Edge::getFirstVertID() { return firstVertID; }
int Edge::getSecondVertID() { return secondVertID; }
bool Edge::getSelected() { return selected; }
bool Edge::getIsBoundary() { return isBoundary; }

void Edge::setFaceIDs(Array<Integer>* param) { faceIDs = param; }
void Edge::setID(int param) { id = param; }
void Edge::setFirstVertID(int param) { firstVertID = param; }
void Edge::setSecondVertID(int param) { secondVertID = param; }
void Edge::setSelected(bool param) { selected = param; }
void Edge::setIsBoundary(bool param) { isBoundary = param; }
