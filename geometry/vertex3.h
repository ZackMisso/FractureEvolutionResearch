#ifndef __VERTEX3_H__
#define __VERTEX3_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "point3.h"
#include "edge3.h"

class Vertex3 {
private:
  Array<Edge3*>* edges;
  Point3 location;
  int id;
  bool selected;
public:
  Vertex3(real x,real y,real z);
  Vertex3(Point3 point);
  ~Vertex3();
  // getter methods
  Array<Edge3*>* getEdges();
  Point3 getLocation();
  int getID();
  bool getSelected();
  // setter methods
  void setEdges(Array<Edge3*>* param);
  void setLocation(Point3 point);
  void setID(int param);
  void setSelected(bool param);
};

#endif
