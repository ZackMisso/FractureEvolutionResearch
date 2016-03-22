#ifndef __SUBAREACROSSOVER_H__
#define __SUBAREACROSSOVER_H__

#include "../../globalInclude.h"
#include "crossoverFunction.h"

class SubAreaCrossover : public CrossoverFunction {
private:
public:
  SubAreaCrossover();
  SubAreaCrossover(real param);
  ~SubAreaCrossover();
  virtual Individual* crossover(Individual* one,Individual* two);
};

#endif
