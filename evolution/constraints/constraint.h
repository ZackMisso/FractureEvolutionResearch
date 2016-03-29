#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

// This class will just be here to extend for now

#include "../../globalInclude.h"
#include "../individual.h"

class Constraint {
private:
public:
  Constraint();
  ~Constraint();
  virtual bool applyConstraint(Individual* individual);
};

#endif
