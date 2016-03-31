#ifndef __IDTRACKER_H__
#define __IDTRACKER_H__

class IDTracker {
private:
  int nextVertID;
  int nextEdgeID;
  int nextFaceID;
public:
  IDTracker();
  IDTracker* copy();
  int incrementNextVert();
  int incrementNextEdge();
  int incrementNextFace();
  // getter methods
  int getNextVertID();
  int getNextEdgeID();
  int getNextFaceID();
  // setter methods
  void setNextVertID(int param);
  void setNextEdgeID(int param);
  void setNextFaceID(int param);
};

#endif
