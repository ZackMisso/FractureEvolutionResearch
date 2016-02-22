#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "array.h"
#include "vertex.h"
#include "edge.h"

class Debug {
public:
  static void printPoints(Array<Vertex*>* verts);
  static void printLines(Array<Edge*>* edges);
};

#endif
