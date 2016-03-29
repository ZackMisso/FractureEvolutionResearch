#ifndef __PENALTY_H__
#define __PENALTY_H__

#include "../../globalInclude.h"
#include "../individual.h"
#include "../constraints/constraint.h"

class Penalty {
private:
  Constraint* constraint;
  real multiplier;
public:
  Penalty();
  ~Penalty();
  real applyPenalty(Individual* individual,real fitness);
  // getter methods
  Constraint* getConstraint();
  real getMultiplier();
  // setter methods
  void setConstraint(Constraint* param);
  void setMultiplier(real param);
};

#endif
