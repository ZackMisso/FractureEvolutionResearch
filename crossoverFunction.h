#ifndef __CROSSOVERFUNCTION_H__
#define __CROSSOVERFUNCTION_H__

#include "globalInclude.h"
#include "individual.h"

class CrossoverFunction {
private:
public:
  CrossoverFunction();
  ~CrossoverFunction();
  virtual Individual* crossover(Individual* one,Individual* two);
};

#endif
