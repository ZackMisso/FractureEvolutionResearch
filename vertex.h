#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "globalInclude.h"
#include "array.h"
#include "edge.h"
#include "point2.h"

class Vertex {
private:
  Array<Edge*> *edges;
  Point2 location; // [0.0-1.0 , 0.0-1.0]
  int id;
  bool selected;
public:
  Vertex(real x,real y);
  Vertex(Point2 point);
  ~Vertex();
	void draw();
  bool isMatch(Point2 point);
  bool isConnected(Vertex* other);
	// getters
	Array<Edge*>* getEdges();
	Point2	getLocation();
  int getID();
  bool getSelected();
	// setters
	void setEdges(Array<Edge*>* param);
	void setLocation(Point2 param);
  void setID(int param);
  void setSelected(bool param);
};

#endif
