#ifndef __EDGECURVECROSSOVER_H__
#define __EDGECURVECROSSOVER_H__

#include "globalInclude.h"
#include "crossoverFunction.h"

class EdgeCurveCrossover : public CrossoverFunction {
private:
public:
  EdgeCurveCrossover();
  EdgeCurveCrossover(real param);
  ~EdgeCurveCrossover();
  virtual Individual* crossover(Individual* one,Individual* two);
};

#endif
