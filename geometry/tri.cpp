#include "tri.h"
// USE ON LINUX
#include <GL/glut.h>
// USE ON MAC
//#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#include <cmath>

#include <iostream>

using namespace std;

Tri::Tri() {
  // adjacents must be created outside of this class
  edges = new Edge*[3];
  //adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  //adjacents[0] = 0x0;
  //adjacents[1] = 0x0;
  //adjacents[2] = 0x0;
  //isBoundary = false;
}

Tri::Tri(Point2 one,Point2 two,Point2 three) {
  points[0] = one;
  points[1] = two;
  points[2] = three;
  edges = new Edge*[3];
  //adjacents = new Tri*[3];
  edges[0] = new Edge(one,two);
  edges[1] = new Edge(two,three);
  edges[2] = new Edge(three,one);
  //adjacents[0] = 0x0;
  //adjacents[1] = 0x0;
  //adjacents[2] = 0x0;
  //isBoundary = false;
}

Tri::Tri(Edge* one,Edge* two,Edge* three) {
  edges = new Edge*[3];
  //adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  //adjacents[0] = 0x0;
  //adjacents[1] = 0x0;
  //adjacents[2] = 0x0;
  //isBoundary = false;
  // to be implemented
}

Tri::Tri(Tri* one,Tri* two,Tri* trhee) {
  edges = new Edge*[3];
  //adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  //adjacents[0] = 0x0;
  //adjacents[1] = 0x0;
  //adjacents[2] = 0x0;
  //isBoundary = false;
  // to be implemented
}

Tri::Tri(Edge* one,Point2 point,int pointID) {
  points[0] = one->getFirst();
  points[1] = one->getSecond();
  points[2] = point;
  pointIDs[0] = one->getFirstVertID();
  pointIDs[1] = one->getSecondVertID();
  pointIDs[2] = pointID;
  edges[0] = one->copy();
  edges[1] = new Edge(points[0],points[2],pointIDs[0],pointIDs[2]);
  edges[2] = new Edge(points[1],points[2],pointIDs[1],pointIDs[2]);
}

Tri::~Tri() {
  delete edges[2];
  delete edges[1];
  delete edges[0];
  delete edges;
  //delete adjacents[2];
  //delete adjacents[1];
  //delete adjacents[0];
  //delete adjacents;
}

// IMPLEMENT THIS LATER INSTEAD OF USING TRIMESH CALCALLADJ
//void Tri::findAdjacents(Array<Tri*>* triangles) {
//  //cout << "NOT IMPLEMENTED :: FIND ADJACENTS" << endl;
//  //for(int i=0;i<triangles->getSize();i++) {
//  //
//  //}
//  // to be implemented
//}

bool Tri::equals(Tri* other) {
  bool equals = true;
  equals = equals && points[0].equals(other->getPointOne());
  equals = equals && points[1].equals(other->getPointTwo());
  equals = equals && points[2].equals(other->getPointThree());
  return equals;
}

// Implement (later) Moller-Trumbore triangle intersection algorithm
bool Tri::isInsideOld(Point2 point) {
  bool b1 = false;
  bool b2 = false;
  bool b3 = false;
  b1 = sign(point,points[0],points[1]) < 0.0;
  b2 = sign(point,points[1],points[2]) < 0.0;
  b3 = sign(point,points[2],points[0]) < 0.0;
  cout << b1 << " " << b2 << " " << b3 << endl;
  bool ret = (b1==b2 && b2==b3);
  cout << "Returning From IsInside: " << ret << endl;
  return (b1==b2 && b2==b3);
}

bool Tri::isInside(Point2 point) {
  Point2 v0;
  Point2 v1;
  Point2 v2;
  v0.xpos = points[2].xpos - points[1].xpos;
  v0.ypos = points[2].ypos - points[1].ypos;
  v1.xpos = points[0].xpos - points[1].xpos;
  v1.ypos = points[0].ypos - points[1].ypos;
  v2.xpos = point.xpos - points[1].xpos;
  v2.ypos = point.ypos - points[1].ypos;
  real dot00 = v0.dot(v0);
  real dot01 = v0.dot(v1);
  real dot02 = v0.dot(v2);
  real dot11 = v1.dot(v1);
  real dot12 = v1.dot(v2);
  real invDen = 1 / (dot00 * dot02 - dot01 * dot01);
  real u = (dot11 * dot02 - dot01 * dot12) * invDen;
  real v = (dot00 * dot12 - dot01 * dot02) * invDen;
  return (u >=0.0) && (v >= 0.0) && (u + v < 1.0);
}

real Tri::sign(Point2 one,Point2 two,Point2 three) {
  real sign = (one.xpos - three.xpos) * (two.ypos - three.ypos) * (two.xpos - three.xpos) - (one.ypos - three.ypos);
  cout << "Sign: " << sign << endl;
  return sign;
}

void Tri::debug() {
  cout << "First :: ";
  points[0].debug();
  cout << "Second :: ";
  points[1].debug();
  cout << "Third :: ";
  points[2].debug();
  cout << endl;
}

void Tri::updatePosition(int id,Point2 newPos) {
  if(pointIDs[2] == id)
    points[2] = newPos;
  else if(pointIDs[1] == id)
    points[1] = newPos;
  else if(pointIDs[0] == id)
    points[0] = newPos;
}

Point2 Tri::interpolatePosition(real baryOne,real baryTwo,real baryThree) {
  Point2 interpolated;
  interpolated.xpos = 0.0;
  interpolated.ypos = 0.0;
  interpolated.xpos += points[0].xpos * baryOne;
  interpolated.xpos += points[1].xpos * baryTwo;
  interpolated.xpos += points[2].xpos * baryThree;
  interpolated.ypos += points[0].ypos * baryOne;
  interpolated.ypos += points[1].ypos * baryTwo;
  interpolated.ypos += points[2].ypos * baryThree;
  return interpolated;
}

//bool Tri::equals(Point2 one,Point2 two,Point2 three) {
//  if()
//}

void Tri::draw() {
  glVertex2f(points[0].xpos,points[0].ypos);
  glVertex2f(points[1].xpos,points[1].ypos);
  glVertex2f(points[2].xpos,points[2].ypos);
}

real Tri::area() {
  real one = edges[0]->length();
  real two = edges[1]->length();
  real three = edges[2]->length();
  real tmp = (one+two+three)/2.0;
  return sqrt(tmp * (tmp - one) * (tmp - two) * (tmp - three));
}

Point2 Tri::getPoint(int num) { return points[num]; }
Point2 Tri::getPointOne() { return points[0]; }
Point2 Tri::getPointTwo() { return points[1]; }
Point2 Tri::getPointThree() { return points[2]; }
int Tri::getPointIDOne() { return pointIDs[0]; }
int Tri::getPointIDTwo() { return pointIDs[1]; }
int Tri::getPointIDThree() { return pointIDs[2]; }
Edge* Tri::getEdge(int num) { return edges[num]; }
Edge* Tri::getEdgeOne() { return edges[0]; }
Edge* Tri::getEdgeTwo() { return edges[1]; }
Edge* Tri::getEdgeThree() { return edges[2]; }
//Tri* Tri::getAdjacent(int num) { return adjacents[num]; }
//Tri* Tri::getAdjacentOne() { return adjacents[0]; }
//Tri* Tri::getAdjacentTwo() { return adjacents[1]; }
//Tri* Tri::getAdjacentThree() { return adjacents[2]; }
//bool Tri::getIsBoundary() { return isBoundary; }

void Tri::setPoint(int num,Point2 param) { points[num] = param; }
void Tri::setPointOne(Point2 param) { points[0] = param; }
void Tri::setPointTwo(Point2 param) { points[1] = param; }
void Tri::setPointThree(Point2 param) { points[2] = param; }
void Tri::setPointIDOne(int param) { pointIDs[0] = param; }
void Tri::setPointIDTwo(int param) { pointIDs[1] = param; }
void Tri::setPointIDThree(int param) { pointIDs[2] = param; }
void Tri::setEdge(int num,Edge* param) { edges[num] = param; }
void Tri::setEdgeOne(Edge* param) { edges[0] = param; }
void Tri::setEdgeTwo(Edge* param) { edges[1] = param; }
void Tri::setEdgeThree(Edge* param) { edges[2] = param; }
//void Tri::setAdjacent(int num,Tri* param) { adjacents[num] = param; }
//void Tri::setAdjacentOne(Tri* param) { adjacents[0] = param; }
//void Tri::setAdjacentTwo(Tri* param) { adjacents[1] = param; }
//void Tri::setAdjacentThree(Tri* param) { adjacents[2] = param; }
//void Tri::setIsBoundary(bool param) { isBoundary = param; }
