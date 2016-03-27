#ifndef __FITNESSFUNCTION_H__
#define __FITNESSFUNCTION_H__

#include "../../globalInclude.h"
#include "../../dataStructures/array.h"
#include "../individual.h"

class FitnessFunction {
private:
public:
  FitnessFunction();
  ~FitnessFunction();
  virtual void preProcess(Array<Individual*>* individuals);
  virtual real getFitness(Individual* individual);
};

#endif
