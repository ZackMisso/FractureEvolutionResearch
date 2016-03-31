#include "idTracker.h"

IDTracker::IDTracker() {
  nextVertID = 0;
  nextEdgeID = 0;
  nextFaceID = 0;
}

IDTracker* IDTracker::copy() {
  IDTracker* tracker = new IDTracker();
  tracker->setNextVertID(nextVertID);
  tracker->setNextEdgeID(nextEdgeID);
  tracker->setNextFaceID(nextFaceID);
  return tracker;
}

int IDTracker::incrementNextVert() {
  return nextVertID++;
}

int IDTracker::incrementNextEdge() {
  return nextEdgeID++;
}

int IDTracker::incrementNextFace() {
  return nextFaceID++;
}

int IDTracker::getNextVertID() { return nextVertID; }
int IDTracker::getNextEdgeID() { return nextEdgeID; }
int IDTracker::getNextFaceID() { return nextFaceID; }

void IDTracker::setNextVertID(int param) { nextVertID = param; }
void IDTracker::setNextEdgeID(int param) { nextEdgeID = param; }
void IDTracker::setNextFaceID(int param) { nextFaceID = param; }
