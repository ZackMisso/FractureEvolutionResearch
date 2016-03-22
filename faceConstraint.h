#ifndef __FACECONSTRAINT_H__
#define __FACECONSTRAINT_H__

#include "face.h"

class FaceConstraint {
private:
public:
  FaceConstraint();
  ~FaceConstraint();
  virtual bool meetsConstraint(Face* face);
};

#endif
