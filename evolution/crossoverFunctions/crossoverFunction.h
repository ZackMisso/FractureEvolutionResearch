#ifndef __CROSSOVERFUNCTION_H__
#define __CROSSOVERFUNCTION_H__

#include "../../globalInclude.h"
#include "../individual.h"

class CrossoverFunction {
private:
  real probability;
public:
  CrossoverFunction();
  CrossoverFunction(real param);
  ~CrossoverFunction();
  virtual Individual* crossover(Individual* one,Individual* two);
  // getter methods
  real getProbability();
  // setter methods
  void setProbability(real param);
};

#endif
