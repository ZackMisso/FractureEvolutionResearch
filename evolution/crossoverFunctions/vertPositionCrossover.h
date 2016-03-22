#ifndef __VERTPOSITIONCROSSOVER_H__
#define __VERTPOSITIONCROSSOVER_H__

#include "../../globalInclude.h"
#include "crossoverFunction.h"

class VertPositionCrossover : public CrossoverFunction {
private:
public:
  VertPositionCrossover();
  VertPositionCrossover(real param);
  ~VertPositionCrossover();
  virtual Individual* crossover(Individual* one,Individual* two);
};

#endif
