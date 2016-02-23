#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "array.h"
#include "vertex.h"
#include "edge.h"
#include "fracture.h"

class Debug {
public:
  static void printPoints(Array<Vertex*>* verts);
  static void printLines(Array<Edge*>* edges);
  static void printFracture(Fracture* fracture);
  static void printLine(Edge* edge);
};

#endif
