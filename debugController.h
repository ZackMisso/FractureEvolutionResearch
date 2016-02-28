#ifndef __DEBUGCONTROLLER_H__
#define __DEBUGCONTROLLER_H__

#include "fracture.h"
#include "vertex.h"
#include "edge.h"

class DebugController {
public:
  static int nextVertNum;
  static int nextEdgeNum;
  static int nextFaceNum;
  // implement more
  static void init();
  static int getNextVert();
  static int getNextEdge();
  static int getNextFace();
  static void writeCreateSeparationPoint(float x,float y);
  static void writeCreateEdge(Edge* newEdge);
  static void writeCreateVert(Vertex* newVert);
  static void writeCreateFace(Face* newFace);
  static void writeDeleteEdge(Edge* oldEdge);
  static void writeDeleteVertex(Vertex* oldVert);
  static void writeDeleteFace(Face* oldFace);
  static void writeDebugState(Fracture* fracture);
  static void writeEdgeState(Edge* edge);
  static void writeVertState(Vertex* vert);
  static void writeFaceState(Face* face);
  static void writeSingleStates(Fracture* fracture);
  static void writeRelationalStates(Fracture* fracture);

  //DebugController::nextFaceNum = 0;
  //DebugController::nextEdgeNum = 0;
  //DebugController::nextVertNum = 0;
};

//int DebugController::nextFaceNum = 0;
//int DebugController::nextEdgeNum = 0;
//int DebugController::nextVertNum = 0;

#endif
