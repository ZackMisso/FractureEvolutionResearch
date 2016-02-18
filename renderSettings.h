#ifndef __RENDERSETTINGS_H__
#define __RENDERSETTINGS_H__

class RenderSettings {
private:
  int vertSize;
  int edgeSize;
  bool displayVerts;
  bool displayEdges;
  bool displayFaces;
public:
  RenderSettings();
  ~RenderSettings();
  // getter methods
  int getVertSize();
  int getEdgeSize();
  bool getDisplayVerts();
  bool getDisplayEdges();
  bool getDisplayFaces();
  // setter methods
  void setVertSize(int param);
  void setEdgeSize(int param);
  void setDisplayVerts(bool param);
  void setDisplayEdges(bool param);
  void setDisplayFaces(bool param);
};

#endif
