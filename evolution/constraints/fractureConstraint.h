#ifndef __FRACTURECONSTRAINT_H__
#define __FRACTURECONSTRAINT_H__

#include "../../globalInclude.h"
#include "../../geometry/fracture.h"

class FractureConstraint {
private:
public:
  FractureConstraint();
  ~FractureConstraint();
  virtual bool meetsConstraint(Fracture* fracture);
};

#endif
