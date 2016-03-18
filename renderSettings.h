#ifndef __RENDERSETTINGS_H__
#define __RENDERSETTINGS_H__

// Causes Linking Errors
//#include "interfaceData.h"

class RenderSettings {
private:
  //InterfaceData* interfaceRef;
  int vertSize;
  int edgeSize;
  bool displayVerts;
  bool displayEdges;
  bool displayFaces;
  bool displayFaceTrimesh;
public:
  RenderSettings();
  ~RenderSettings();
  // getter methods
  //InterfaceData* getInterfaceRef();
  int getVertSize();
  int getEdgeSize();
  bool getDisplayVerts();
  bool getDisplayEdges();
  bool getDisplayFaces();
  bool getDisplayFaceTrimesh();
  // setter methods
  //void setInterfaceRef(InterfaceData* param);
  void setVertSize(int param);
  void setEdgeSize(int param);
  void setDisplayVerts(bool param);
  void setDisplayEdges(bool param);
  void setDisplayFaces(bool param);
  void setDisplayFaceTrimesh(bool param);
};

#endif
