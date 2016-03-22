#ifndef __MUTATIONFUNCTION_H__
#define __MUTATIONFUNCTION_H__

// Creating this so this project can easily be extendable in the future

#include "../../globalInclude.h"
#include "../individual.h"

class MutationFunction {
private:
  real probability;
public:
  MutationFunction();
  MutationFunction(real param);
  ~MutationFunction();
  virtual Individual* mutate(Individual* individual);
  // getter methods
  real getProbability();
  // setter methods
  void setProbability(real param);
};

#endif
