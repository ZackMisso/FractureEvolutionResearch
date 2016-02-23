#include "edge.h"
#include <GL/glut.h>
#include "debug.h"

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
  //cout << "////////////////////////////////////////" << endl;
  Point2 oFirst = other->getFirst();
  Point2 oSecond = other->getSecond();

  //cout << "TWO :: " << oFirst.xpos << " " << oFirst.ypos << " " << oSecond.xpos << " " << oSecond.ypos << endl;
  //cout << "ONE :: " << first.xpos << " " << first.ypos << " " << second.xpos << " " << second.ypos << endl;

  float s1x = first.xpos - second.xpos;
  float s1y = first.ypos - second.ypos;
  float s2x = oFirst.xpos - oSecond.xpos;
  float s2y = oFirst.ypos - oSecond.ypos;

  //cout << "S1X :: " << s1x << endl;
  //cout << "S2X :: " << s2x << endl;
  //cout << "S1Y :: " << s1y << endl;
  //cout << "S2Y :: " << s2y << endl;

  float det = -s2x * s1y + s1x * s2y;

  //if(det<0)
  //  det*=-1;

  //cout << "Det :: " << det << endl;

  if(det == 0.0f)
    return false;

  float tmp1 = (first.xpos - oFirst.xpos);
  float tmp2 = (first.ypos - oFirst.ypos);

  float s = (-s1y * tmp1 + s1x * tmp2) / det;
  float t = (-s2y * tmp1 + s2x * tmp2) / det;

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
    if(edges->get(i)!=ignore) {
      cout << "Calling Intersects" << endl;
      if(intersects(edges->get(i)))
        return edges->get(i);
    }
  return 0x0;
}

Point2 Edge::getIntersectionPoint(Edge* other) {
  cout << "//////////////////////////////////" << endl;
  cout << "This Edge :: " << endl;
  Debug::printLine(this);
  cout << "Other Edge :: " << endl;
  Debug::printLine(other);
  Point2 intersection;
  intersection.xpos = -1;
  intersection.ypos = -1;
  Point2 oFirst = other->getFirst();
  Point2 oSecond = other->getSecond();
  float s1x = first.xpos - second.xpos;
  float s1y = first.ypos - second.ypos;
  float s2x = oFirst.xpos - oSecond.xpos;
  float s2y = oFirst.ypos - oSecond.ypos;
  float det = -s2x * s1y + s1x * s2y;
  float tmp1 = (first.xpos - oFirst.xpos);
  float tmp2 = (first.ypos - oFirst.ypos);
  float s = (-s1y * tmp1 + s1x * tmp2) / det;
  float t = (-s2y * tmp1 + s2x * tmp2) / det;
  s*=-1;
  t*=-1;
  cout << "s1x :: " << s1x << endl;
  cout << "s1y :: " << s1y << endl;
  cout << "s2x :: " << s2x << endl;
  cout << "s2y :: " << s2y << endl;
  cout << "T :: " << t << endl;
  cout << "S :: " << s << endl;
  cout << "Xpos :: " << first.xpos << endl;
  cout << "Ypos :: " << first.ypos << endl;
  intersection.xpos = first.xpos - t * s1x;
  intersection.ypos = first.ypos - t * s1y;
  cout << "INTERSECTION :: " << endl;
  Debug::printPoint(intersection);
  cout << "///////////////!!!///////////////////" << endl;
  return intersection;
}

bool Edge::eitherMatch(Point2 point) {
  if(first.xpos == point.xpos && first.ypos == point.ypos)
    return true;
  if(second.xpos == point.xpos && second.ypos == point.ypos)
    return true;
  return false;
}

Point2 Edge::getOtherPoint(Point2 point) {
  if(point.xpos == first.xpos && point.ypos == first.ypos)
    return second;
  return first;
}

Point2 Edge::getPointBetween(float linePos) {
  Point2 newPoint;
  newPoint.xpos = ((second.xpos-first.xpos) * linePos) + first.xpos;
  newPoint.ypos = ((second.ypos-first.ypos) * linePos) + first.ypos;
  return newPoint;
}

void Edge::split(Array<Edge*>* cb,Point2 point) {
  cb->add(new Edge(first,point));
  cb->add(new Edge(point,second));
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
