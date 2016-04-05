#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "../dataStructures/integer.h"
#include "edge.h"
#include "point2.h"

class Vertex {
private:
  Array<Edge*> *edges;
  Array<Integer>* faceIDs;
  Point2 location; // [0.0-1.0 , 0.0-1.0]
  int id;
  bool selected;
  bool boundary;
  bool isCorner;
public:
  Vertex(real x,real y);
  Vertex(Point2 point);
  ~Vertex();
  Vertex* copy(Array<Edge*>* newEdges);
	void draw();
  void updateEdges();
  void updateFaceIDs();
  bool isMatch(Point2 point);
  bool isConnected(Vertex* other);
	// getters
	Array<Edge*>* getEdges();
  Array<Integer>* getFaceIDs();
	Point2	getLocation();
  int getID();
  bool getSelected();
  bool getBoundary();
  bool getIsCorner();
	// setters
	void setEdges(Array<Edge*>* param);
  void setFaceIDs(Array<Integer>* param);
	void setLocation(Point2 param);
  void setID(int param);
  void setSelected(bool param);
  void setBoundary(bool param);
  void setIsCorner(bool param);
};

#endif
