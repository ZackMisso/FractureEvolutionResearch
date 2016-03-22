#ifndef __FRACTURECONSTRAINT_H__
#define __FRACTURECONSTRAINT_H__

#include "fracture.h"

class FractureConstraint {
private:
public:
  FractureConstraint();
  ~FractureConstraint();
  virtual bool meetsConstraint(Fracture* fracture);
};

#endif
