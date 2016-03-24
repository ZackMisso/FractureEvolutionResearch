#include "penalty.h"

Penalty::Penalty() {
  constraint = 0x0;
  multiplier = 0;
}

Penaly::~Penalty() {
  delete constraint;
}

real Penalty::applyPenalty(Individual* individual,real fitness) {
  if(constraint->applyConstraint(individual))
    return fitness*penalty;
  return fitness;
}
