#ifndef __FACECONSTRAINT_H__
#define __FACECONSTRAINT_H__

#include "../../globalInclude.h"
#include "constraint.h"
#include "../../geometry/face.h"

class FaceConstraint : public Constraint {
private:
public:
  FaceConstraint();
  ~FaceConstraint();
  virtual bool meetsConstraint(Face* face);
  virtual bool applyConstraint(Individual* individual);
};

#endif
