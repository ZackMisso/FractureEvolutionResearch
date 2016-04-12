#ifndef __RENDERSETTINGS_H__
#define __RENDERSETTINGS_H__

#include "../globalInclude.h"

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
  // display demos
  bool triangulationOne;
  bool triangulationTwo;
  bool vertAddConvexOne;
  bool vertAddConvexTwo;
  bool vertAddConvexThree;
  bool vertAddConcaveOne;
  bool vertAddConcaveTwo;
  bool vertAddConcaveThree;
  bool vertAddConcaveFour;
  bool vertAddConcaveFive;
  bool vertMoveConvexOne;
  bool vertMoveConvexTwo;
  bool vertMoveConcaveOne;
  bool vertMoveConcaveTwo;
public:
  RenderSettings();
  ~RenderSettings();
  void resetDisplay();
  // getter methods
  //InterfaceData* getInterfaceRef();
  int getVertSize();
  int getEdgeSize();
  bool getDisplayVerts();
  bool getDisplayEdges();
  bool getDisplayFaces();
  bool getDisplayFaceTrimesh();
  bool getTriangulationOne();
  bool getTriangulationTwo();
  bool getVertAddConvexOne();
  bool getVertAddConvexTwo();
  bool getVertAddConvexThree();
  bool getVertAddConcaveOne();
  bool getVertAddConcaveTwo();
  bool getVertAddConcaveThree();
  bool getVertAddConcaveFour();
  bool getVertAddConcaveFive();
  bool getVertMoveConvexOne();
  bool getVertMoveConvexTwo();
  bool getVertMoveConcaveOne();
  bool getVertMoveConcaveTwo();
  // setter methods
  //void setInterfaceRef(InterfaceData* param);
  void setVertSize(int param);
  void setEdgeSize(int param);
  void setDisplayVerts(bool param);
  void setDisplayEdges(bool param);
  void setDisplayFaces(bool param);
  void setDisplayFaceTrimesh(bool param);
  void setTriangulationOne(bool param);
  void setTriangulationTwo(bool param);
  void setVertAddConvexOne(bool param);
  void setVertAddConvexTwo(bool param);
  void setVertAddConvexThree(bool param);
  void setVertAddConcaveOne(bool param);
  void setVertAddConcaveTwo(bool param);
  void setVertAddConcaveThree(bool param);
  void setVertAddConcaveFour(bool param);
  void setVertAddConcaveFive(bool param);
  void setVertMoveConvexOne(bool param);
  void setVertMoveConvexTwo(bool param);
  void setVertMoveConcaveOne(bool param);
  void setVertMoveConcaveTwo(bool param);
};

#endif
