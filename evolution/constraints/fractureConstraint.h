#ifndef __FRACTURECONSTRAINT_H__
#define __FRACTURECONSTRAINT_H__

#include "../../globalInclude.h"
#include "constraint.h"
#include "../../geometry/fracture.h"

class FractureConstraint : public Constraint {
private:
public:
  FractureConstraint();
  ~FractureConstraint();
  virtual bool meetsConstraint(Fracture* fracture);
  virtual bool applyConstraint(Individual* individual);
};

#endif
