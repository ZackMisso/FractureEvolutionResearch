#ifndef __FITNESSFUNCTION_H__
#define __FITNESSFUNCTION_H__

#include "globalInclude.h"
#include "individual.h"

class FitnessFunction {
private:
public:
  FitnessFunction();
  ~FitnessFunction();
  virtual float getFitness(Individual* individual);
};

#endif
