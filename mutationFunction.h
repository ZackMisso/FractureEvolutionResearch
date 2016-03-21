#ifndef __MUTATIONFUNCTION_H__
#define __MUTATIONFUNCTION_H__

// Creating this so this project can easily be extendable in the future

#include "globalInclude.h"
#include "individual.h"

class MutationFunction {
private:
public:
  MutationFunction();
  ~MutationFunction();
  virtual Individual* mutate(Individual* individual);
};

#endif
