#include "tests.h"
#include "edge.h"
#include "face.h"
#include "vertex.h"

#include <iostream>

using namespace std;

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
  Point2 one=Point2(-.25,.3);
  Point2 two=Point2(-.05,.3);
  Point2 three=Point2(.3,.3);
  Point2 four=Point2(.3,.1);
  Point2 five=Point2(.3,-1.2);
  Point2 six=Point2(.3,-.4);
  Point2 seven=Point2(0.1,-.4);
  Point2 eight=Point2(-.25,-.4);
  Point2 nine=Point2(-.25,-.1);
  Point2 ten=Point2(-.25,.25);
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
  Array<Edge*>* edges = new Array<Edge*>();
  edges->add(new Edge(one,two));
  edges->add(new Edge(nine,ten));
  edges->add(new Edge(two,three));
  edges->add(new Edge(seven,eight));
  edges->add(new Edge(three,four));
  edges->add(new Edge(ten,one));
  edges->add(new Edge(six,seven));
  edges->add(new Edge(eight,nine));
  edges->add(new Edge(five,six));
  edges->add(new Edge(four,five));
  Face* face = new Face();
  face->setEdges(edges);
  Array<Point2>* sortedPoints = face->sortPointsByPath();
  if(sortedPoints->getSize() != points->getSize()) {
    //cout << "Size :: " << sortedPoints->getSize() << endl;
    //cout << "Correct Size :: " << points->getSize() << endl;
    return true;
  }
  for(int i=0;i<sortedPoints->getSize();i++) {
    if(!sortedPoints->get(i).equals(points->get(i))) {
      //for(int j=0;j<sortedPoints->getSize();j++)
      //  sortedPoints->get(j).debug();
      return true;
    }
  }
  return false;
}

bool Tests::vertReverseTest() {
  Array<Point2>* points = new Array<Point2>();
  Point2 one=Point2(-.25,.3);
  Point2 two=Point2(-.05,.3);
  Point2 three=Point2(.3,.3);
  Point2 four=Point2(.3,.1);
  Point2 five=Point2(.3,-1.2);
  Point2 six=Point2(.3,-.4);
  Point2 seven=Point2(0.1,-.4);
  Point2 eight=Point2(-.25,-.4);
  Point2 nine=Point2(-.25,-.1);
  Point2 ten=Point2(-.25,.25);
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
  Array<Point2>* reversedPoints = new Array<Point2>();
  while(points->getSize())
    reversedPoints->add(points->removeLast());
  delete points;
  Array<Edge*>* edges = new Array<Edge*>();
  edges->add(new Edge(one,two));
  edges->add(new Edge(nine,ten));
  edges->add(new Edge(two,three));
  edges->add(new Edge(seven,eight));
  edges->add(new Edge(three,four));
  edges->add(new Edge(ten,one));
  edges->add(new Edge(six,seven));
  edges->add(new Edge(eight,nine));
  edges->add(new Edge(five,six));
  edges->add(new Edge(four,five));
  Face* face = new Face();
  face->setEdges(edges);
  Array<Point2>* sortedPoints = face->sortPointsByPath();
  sortedPoints = face->reversePath(sortedPoints);
  if(sortedPoints->getSize() != points->getSize()) {
    //cout << "Sorted Points not the same size" << endl;
    return true;
  }
  for(int i=0;i<sortedPoints->getSize();i++) {
    if(!sortedPoints->get(i).equals(reversedPoints->get(i)))
      return true;
  }
  return false;
}

// NOT NEEDED
//bool Tests::edgeIsOnTest() { // implement Data
//  // horizontal test no overlap
//  Edge* oneA = new Edge(0,0,1,0);
//  Edge* twoA = new Edge(1.2,0,2,0);
//  // horizontal test overlap
//  Edge* oneB = new Edge(0,0,1,0);
//  Edge* twoB = new Edge(.5,0,2,0);
//  // vertical test no overlap
//  Edge* oneC = new Edge(0,2,0,3);
//  Edge* twoC = new Edge(0,0,0,1);
//  // vertical test overlap
//  Edge* oneD = new Edge(0,.5,0,1.5);
//  Edge* twoD = new Edge(0,0,0,1);
//  // opposite slopes test
//  Edge* oneE = new Edge(-.5,-.5,.5,.5);
//  Edge* twoE = new Edge(-.5,.5,.5,-.5);
//  // same slopes different b test
//  Edge* oneF = new Edge(0,0,2,6);
//  Edge* twoF = new Edge(0,2,2,8);
//  // same slopes same b test
//  Edge* oneG = new Edge(0,0,2,6);
//  Edge* twoG = new Edge(0,0,2,6);
//  /*if(oneA->isOn(twoA)) {
//    cout << "First Test Failed" << endl;
//    return true;
//  }
//  if(!oneB->isOn(twoB)) {
//    cout << "Second Test Failed" << endl;
//    return true;
//  }
//  if(oneC->isOn(twoC)) {
//    cout << "Third Test Failed" << endl;
//    return true;
//  }
//  if(!oneD->isOn(twoD)) {
//    cout << "Fourth Test Failed" << endl;
//    return true;
//  }
//  if(oneE->isOn(twoE)) {
//    cout << "Fifth Test Failed" << endl;
//    return true;
//  }
//  if(oneF->isOn(twoF)) {
//    cout << "Sixth Test Failed" << endl;
//    return true;
//  }
//  if(!oneG->isOn(twoG)) {
//    cout << "Sevent Test Failed" << endl;
//    return true;
//  }*/
//  return false;
//}

//bool Tests::adjacentsTest() {
//  // to be implemented
//  return true;
//}

bool Tests::detectIfConvexTest() { // implement Data
  Face* convexFace = new Face();
  Face* concaveFace = new Face();
  Point2 one = Point2(-.25,.25);
  Point2 two = Point2(.25,.25);
  Point2 three = Point2(.5,-.1);
  Point2 four = Point2(.25,-.3);
  Point2 five = Point2(-.25,-.3);
  Point2 sixOne = Point2(-.5,-.1);
  Point2 sixTwo = Point2(-.05,-.1);
  Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();
  Array<Vertex*>* oneVerts = new Array<Vertex*>();
  Array<Vertex*>* twoVerts = new Array<Vertex*>();
  Edge* eOne = new Edge(one,two);
  Edge* eTwo = new Edge(two,three);
  Edge* eThree = new Edge(three,four);
  Edge* eFour = new Edge(four,five);
  Edge* eFiveOne = new Edge(five,sixOne);
  Edge* eFiveTwo = new Edge(five,sixTwo);
  Edge* eSixOne = new Edge(sixOne,one);
  Edge* eSixTwo = new Edge(sixTwo,one);
  oneEdges->add(eOne);
  oneEdges->add(eTwo);
  oneEdges->add(eThree);
  oneEdges->add(eFour);
  oneEdges->add(eFiveOne);
  oneEdges->add(eSixOne);
  twoEdges->add(eOne);
  twoEdges->add(eTwo);
  twoEdges->add(eThree);
  twoEdges->add(eFour);
  twoEdges->add(eFiveTwo);
  twoEdges->add(eSixTwo);
  oneVerts->add(new Vertex(one));
  oneVerts->add(new Vertex(two));
  oneVerts->add(new Vertex(three));
  oneVerts->add(new Vertex(four));
  oneVerts->add(new Vertex(five));
  oneVerts->add(new Vertex(sixOne));
  twoVerts->add(new Vertex(one));
  twoVerts->add(new Vertex(two));
  twoVerts->add(new Vertex(three));
  twoVerts->add(new Vertex(four));
  twoVerts->add(new Vertex(five));
  twoVerts->add(new Vertex(sixTwo));
  convexFace->setVerts(oneVerts);
  convexFace->setEdges(oneEdges);
  concaveFace->setVerts(twoVerts);
  concaveFace->setEdges(twoEdges);
  convexFace->detectIfConvex();
  concaveFace->detectIfConvex();
  if(!convexFace->getIsConvex()) {
    cout << "Convex is not Convex" << endl;
    return true;
  }
  if(concaveFace->getIsConvex()) {
    cout << "Concave Face is Convex" << endl;
    return true;
  }
  // TODO :: DELETE STUFFS
  return false;
}

bool Tests::convexSplitTest() {
  Face* convexFace = new Face();
  //Face* concaveFace = new Face();
  Point2 one = Point2(0,0);
  Point2 two = Point2(0,0);
  Point2 three = Point2(0,0);
  Point2 four = Point2(0,0);
  Point2 five = Point2(0,0);
  Point2 sixOne = Point2(0,0);
  //Point2 sixTwo();
  Array<Edge*>* oneEdges = new Array<Edge*>();
  //Array<Edge*>* twoEdges = new Array<Edge*>();
  Array<Vertex*>* oneVerts = new Array<Vertex*>();
  //Array<Vertex*>* twoVerts = new Array<Vertex*>();
  Edge* eOne = new Edge(one,two);
  Edge* eTwo = new Edge(two,three);
  Edge* eThree = new Edge(three,four);
  Edge* eFour = new Edge(four,five);
  Edge* eFiveOne = new Edge(five,sixOne);
  //Edge* eFiveTwo = new Edge(five,sixTwo);
  Edge* eSixOne = new Edge(sixOne,one);
  //Edge* eSixTwo = new Edge(sixTwo,one);
  oneEdges->add(eOne);
  oneEdges->add(eTwo);
  oneEdges->add(eThree);
  oneEdges->add(eFour);
  oneEdges->add(eFiveOne);
  oneEdges->add(eSixOne);
  //twoEdges->add(eOne);
  //twoEdges->add(eTwo);
  //twoEdges->add(eThree);
  //twoEdges->add(eFour);
  //twoEdges->add(eFiveTwo);
  //twoEdges->add(eSixTwo);
  oneVerts->add(new Vertex(one));
  oneVerts->add(new Vertex(two));
  oneVerts->add(new Vertex(three));
  oneVerts->add(new Vertex(four));
  oneVerts->add(new Vertex(five));
  oneVerts->add(new Vertex(sixOne));
  //twoVerts->add(new Vertex(one));
  //twoVerts->add(new Vertex(two));
  //twoVerts->add(new Vertex(three));
  //twoVerts->add(new Vertex(four));
  //twoVerts->add(new Vertex(five));
  //twoVerts->add(new Vertex(sixTwo));
  convexFace->setVerts(oneVerts);
  convexFace->setEdges(oneEdges);
  //concaveFace->setVerts(twoVerts);
  //concaveFace->setEdges(twoEdges);
  convexFace->splitIntoTrimesh();
  // Create Correct Tris
  // Do Check
  // to be implemented
  return true;
}

bool Tests::concaveSplitTest() {
  // to be implemented
  //Face* convexFace = new Face();
  Face* concaveFace = new Face();
  Point2 one = Point2(0,0);
  Point2 two = Point2(0,0);
  Point2 three = Point2(0,0);
  Point2 four = Point2(0,0);
  Point2 five = Point2(0,0);
  //Point2 sixOne();
  Point2 sixTwo = Point2(0,0);
  //Array<Edge*>* oneEdges = new Array<Edge*>();
  Array<Edge*>* twoEdges = new Array<Edge*>();
  //Array<Vertex*>* oneVerts = new Array<Vertex*>();
  Array<Vertex*>* twoVerts = new Array<Vertex*>();
  Edge* eOne = new Edge(one,two);
  Edge* eTwo = new Edge(two,three);
  Edge* eThree = new Edge(three,four);
  Edge* eFour = new Edge(four,five);
  //Edge* eFiveOne = new Edge(five,sixOne);
  Edge* eFiveTwo = new Edge(five,sixTwo);
  //Edge* eSixOne = new Edge(sixOne,one);
  Edge* eSixTwo = new Edge(sixTwo,one);
  //oneEdges->add(eOne);
  //oneEdges->add(eTwo);
  //oneEdges->add(eThree);
  //oneEdges->add(eFour);
  //oneEdges->add(eFiveOne);
  //oneEdges->add(eSixOne);
  twoEdges->add(eOne);
  twoEdges->add(eTwo);
  twoEdges->add(eThree);
  twoEdges->add(eFour);
  twoEdges->add(eFiveTwo);
  twoEdges->add(eSixTwo);
  //oneVerts->add(new Vertex(one));
  //oneVerts->add(new Vertex(two));
  //oneVerts->add(new Vertex(three));
  //oneVerts->add(new Vertex(four));
  //oneVerts->add(new Vertex(five));
  //oneVerts->add(new Vertex(sixOne));
  twoVerts->add(new Vertex(one));
  twoVerts->add(new Vertex(two));
  twoVerts->add(new Vertex(three));
  twoVerts->add(new Vertex(four));
  twoVerts->add(new Vertex(five));
  twoVerts->add(new Vertex(sixTwo));
  //convexFace->setVerts(oneVerts);
  //convexFace->setEdges(oneEdges);
  concaveFace->setVerts(twoVerts);
  concaveFace->setEdges(twoEdges);
  //convexFace->detectIfConvex();
  //concaveFace->detectIfConvex();
  concaveFace->splitIntoTrimeshConcave();
  // Create Correct Tris
  // Do Check
  // to be implemented
  return true;
}

bool Tests::trimeshCreationTest() {
  // This is probably not even needed
  return false;
}
