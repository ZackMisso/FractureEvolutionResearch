#include "tests.h"
#include "edge.h"

bool Tests::intersectionTestOne() {
  Edge* one = new Edge(-1,4,1,4);
  Edge* two = new Edge(0,6,0,2);
  if(one->intersects(two))
    return false;
  return true;
}

bool Tests::intersectionTestTwo() {
  Edge* one = new Edge(-1,7,1,7);
  Edge* two = new Edge(0,6,0,2);
  if(one->intersects(two))
    return true;
  return false;
}

bool Tests::intersectionTestThree() {
  Edge* two = new Edge(-1,4,1,4);
  Edge* one = new Edge(0,6,0,2);
  if(one->intersects(two))
    return false;
  return true;
}

bool Tests::pointBetweenTest() {
  Edge* one = new Edge(-.5,-.5,-.5,.5);
  Point2 point = one->getPointBetween(.25);
  if(point.xpos != -.5 && point.ypos != -.25)
    return true;
  return false;
}
