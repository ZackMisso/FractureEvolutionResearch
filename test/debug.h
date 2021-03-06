#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "../geometry/vertex.h"
#include "../geometry/edge.h"
#include "../geometry/fracture.h"
#include "../geometry/point2.h"

class Debug {
public:
  static void printPoints(Array<Vertex*>* verts);
  static void printPoint(Point2 point);
  static void printLines(Array<Edge*>* edges);
  static void printFracture(Fracture* fracture);
  static void printLine(Edge* edge);
  static void printVert(Vertex* vert);
  static void printFace(Face* face);
};

#endif
