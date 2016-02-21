#include "edge.h"
#include <GL/glut.h>

#include <iostream>

using namespace std;

Edge::Edge(Point2 one,Point2 two) {
  first.xpos = one.xpos;
  first.ypos = one.ypos;
  second.xpos = two.xpos;
  second.ypos = two.ypos;
  selected = false;
}

Edge::Edge(float x,float y,float xx,float yy) {
  first.xpos = x;
  first.ypos = y;
  second.xpos = xx;
  second.ypos = yy;
  selected = false;
}

void Edge::draw() {
	glVertex2f(first.xpos,first.ypos);
  glVertex2f(second.xpos,second.ypos);
}

bool Edge::intersects(Edge* other) {
  cout << "////////////////////////////////////////" << endl;
  Point2 oFirst = other->getFirst();
  Point2 oSecond = other->getSecond();

  cout << "TWO :: " << oFirst.xpos << " " << oFirst.ypos << " " << oSecond.xpos << " " << oSecond.ypos << endl;
  cout << "ONE :: " << first.xpos << " " << first.ypos << " " << second.xpos << " " << second.ypos << endl;

  float s1x = first.xpos - second.xpos;
  float s1y = first.ypos - second.ypos;
  float s2x = oFirst.xpos - oSecond.xpos;
  float s2y = oFirst.ypos - oSecond.ypos;

  cout << "S1X :: " << s1x << endl;
  cout << "S2X :: " << s2x << endl;
  cout << "S1Y :: " << s1y << endl;
  cout << "S2Y :: " << s2y << endl;

  float det = -s2x * s1y + s1x * s2y;

  cout << "Det :: " << det << endl;

  if(det == 0.0f)
    return false;

  float tmp1 = (first.xpos - oFirst.xpos);
  float tmp2 = (first.ypos - oFirst.ypos);

  float s = -s1y * tmp1 + s1x * tmp2;
  float t = -s2y * tmp1 + s2x * tmp2;

  cout << "S :: " << s << endl;
  cout << "T :: " << t << endl;

  cout << "////////////////////////////////////////" << endl;

  if(s > 0 && s < det && t > 0 && t < det)
    return true;



  return false;
}

Point2 Edge::getIntersectionPoint(Edge* other) {
  Point2 intersection;
  intersection.xpos = -1;
  intersection.ypos = -1;
  // to be implemented
  return intersection;
}

Point2 Edge::getOtherPoint(Point2 point) {
  if(point.xpos == first.xpos && point.ypos == first.ypos)
    return second;
  return first;
}

Point2 Edge::getPointBetween(float linePos) {
  Point2 newPoint;
  newPoint.xpos = (second.xpos-first.xpos) * linePos;
  newPoint.ypos = (second.ypos-first.ypos) * linePos;
  return newPoint;
}

Point2 Edge::getFirst() { return first; }
Point2 Edge::getSecond() { return second; }

void Edge::setFirst(Point2 point) {
  first.xpos = point.xpos;
  first.ypos = point.ypos;
}

void Edge::setSecond(Point2 point) {
  second.xpos = point.xpos;
  second.ypos = point.ypos;
}
