#ifndef __STDDEVFITNESS_H__
#define __STDDEVFITNESS_H__

#include "../../globalInclude.h"
#include "fitnessFunction.h"

class StdDevFitness : public FitnessFunction {
private:
  //real xbar;
public:
  StdDevFitness();
  ~StdDevFitness();
  virtual void preProcess(Array<Individual*>* individuals);
  virtual real getFitness(Individual* individual);
  // getter methods
  //real getXBar();
  // setter methods
  //void setXBar(real param);
};

#endif
