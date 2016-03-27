#ifndef __SELECTDATA_H__
#define __SELECTDATA_H__

#include "../globalInclude.h"
#include "../geometry/vertex.h"
#include "../geometry/edge.h"
#include "../geometry/face.h"

class SelectData {
private:
  Vertex* selectedVert;
  Edge* selectedEdge;
  Face* selectedFace;
public:
  SelectData();
  ~SelectData();
  // getter methods
  Vertex* getSelectedVert();
  Edge* getSelectedEdge();
  Face* getSelectedFace();
  // setter methods
  void setSelectedVert(Vertex* param);
  void setSelectedEdge(Edge* param);
  void setSelectedFace(Face* param);
};

#endif
