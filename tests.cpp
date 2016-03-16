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

bool Tests::vertSortTest() {
  Array<Point2>* points = new Array<Point2>();
  Point2 one(0,0);
  Point2 two(0,0);
  Point2 three(0,0);
  Point2 four(0,0);
  Point2 five(0,0);
  Point2 six(0,0);
  Point2 seven(0,0);
  Point2 eight(0,0);
  Point2 nine(0,0);
  Point2 ten(0,0);
  points->add(one);
  points->add(two);
  points->add(three);
  points->add(four);
  points->add(five);
  points->add(six);
  points->add(seven);
  points->add(eight);
  points->add(nine);
  points->add(ten);
  Array<Edge*> edges = new Array<Edge*>();
  edges->add(new Edge(one,two));
  edges->add(new Edge(two,three));
  edges->add(new Edge(three,four));
  edges->add(new Edge(four,five));
  edges->add(new Edge(five,six));
  edges->add(new Edge(six,seven));
  edges->add(new Edge(seven,eight));
  edges->add(new Edge(eight,nine));
  edges->add(new Edge(nine,ten));
  edges->add(new Edge(ten,one));
  Face* face = new Face();
  face->setEdges(edges);
  Array<Point2>* sortedPoints = face->sortPointsByPath();
  if(sortedPoints->getSize() != points->getSize())
    return true;
  for(int i=0;i<sortedPoints->getSize();i++) {
    if(!sortedPoints->get(i).equals(points->get(i)))
      return true;
  }
  // check the sorted Points are correct
  return false;
}

bool Tests::vertReverseTest() {
  // to be implemented
  return true;
}

bool Tests::edgeIsOnTest() {
  // to be implemented
  return true;
}

bool Tests::adjacentsTest() {
  // to be implemented
  return true;
}

bool Tests::convexSplitTest() {
  // to be implemented
  return true;
}

bool Tests::concaveSplitTest() {
  // to be implemented
  return true;
}

bool Tests::trimeshCreationTest() {
  // to be implemented
  return true;
}
