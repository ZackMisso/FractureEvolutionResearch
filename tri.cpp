#include "tri.h"
// USE ON LINUX
#include <GL/glut.h>
// USE ON MAC
//#include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
//#include <GLUT/glut.h>

#include <iostream>

using namespace std;

Tri::Tri() {
  // adjacents must be created outside of this class
  edges = new Edge*[3];
  adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  adjacents[0] = 0x0;
  adjacents[1] = 0x0;
  adjacents[2] = 0x0;
  isBoundary = false;
}

Tri::Tri(Point2 one,Point2 two,Point2 three) {
  points[0] = one;
  points[1] = two;
  points[2] = three;
  edges = new Edge*[3];
  adjacents = new Tri*[3];
  edges[0] = new Edge(one,two);
  edges[1] = new Edge(two,three);
  edges[2] = new Edge(three,one);
  adjacents[0] = 0x0;
  adjacents[1] = 0x0;
  adjacents[2] = 0x0;
  isBoundary = false;
}

Tri::Tri(Edge* one,Edge* two,Edge* three) {
  edges = new Edge*[3];
  adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  adjacents[0] = 0x0;
  adjacents[1] = 0x0;
  adjacents[2] = 0x0;
  isBoundary = false;
  // to be implemented
}

Tri::Tri(Tri* one,Tri* two,Tri* trhee) {
  edges = new Edge*[3];
  adjacents = new Tri*[3];
  edges[0] = 0x0;
  edges[1] = 0x0;
  edges[2] = 0x0;
  adjacents[0] = 0x0;
  adjacents[1] = 0x0;
  adjacents[2] = 0x0;
  isBoundary = false;
  // to be implemented
}

Tri::~Tri() {
  delete edges[2];
  delete edges[1];
  delete edges[0];
  delete adjacents[2];
  delete adjacents[1];
  delete adjacents[0];
}

void Tri::findAdjacents(Array<Tri*>* triangles) {
  cout << "NOT IMPLEMENTED :: FIND ADJACENTS" << endl;
  // to be implemented
}

void Tri::draw() {
  glVertex2f(points[0].xpos,points[0].ypos);
  glVertex2f(points[1].xpos,points[1].ypos);
  glVertex2f(points[2].xpos,points[2].ypos);
}

Point2 Tri::getPoint(int num) { return points[num]; }
Point2 Tri::getPointOne() { return points[0]; }
Point2 Tri::getPointTwo() { return points[1]; }
Point2 Tri::getPointThree() { return points[2]; }
Edge* Tri::getEdge(int num) { return edges[num]; }
Edge* Tri::getEdgeOne() { return edges[0]; }
Edge* Tri::getEdgeTwo() { return edges[1]; }
Edge* Tri::getEdgeThree() { return edges[2]; }
Tri* Tri::getAdjacent(int num) { return adjacents[num]; }
Tri* Tri::getAdjacentOne() { return adjacents[0]; }
Tri* Tri::getAdjacentTwo() { return adjacents[1]; }
Tri* Tri::getAdjacentThree() { return adjacents[2]; }
bool Tri::getIsBoundary() { return isBoundary; }

void Tri::setPoint(int num,Point2 param) { points[num] = param; }
void Tri::setPointOne(Point2 param) { points[0] = param; }
void Tri::setPointTwo(Point2 param) { points[1] = param; }
void Tri::setPointThree(Point2 param) { points[2] = param; }
void Tri::setEdge(int num,Point2 param) { edges[num] = param; }
void Tri::setEdgeOne(Edge* param) { edges[0] = param; }
void Tri::setEdgeTwo(Edge* param) { edges[1] = param; }
void Tri::setEdgeThree(Edge* param) { edges[2] = param; }
void Tri::setAdjacent(int num,Tri* param) { adjacents[num] = param; }
void Tri::setAdjacentOne(Tri* param) { adjacents[0] = param; }
void Tri::setAdjacentTwo(Tri* param) { adjacents[1] = param; }
void Tri::setAdjacentThree(Tri* param) { adjacents[2] = param; }
void Tri::setIsBoundary(bool param) { isBoundary = param; }
