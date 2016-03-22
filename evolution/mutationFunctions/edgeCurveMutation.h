#ifndef __EDGECURVEMUTATION_H__
#define __EDGECURVEMUTATION_H__

#include "../../globalInclude.h"
#include "mutationFunction.h"

class EdgeCurveMutation : public MutationFunction {
private:
public:
  EdgeCurveMutation();
  EdgeCurveMutation(real param);
  ~EdgeCurveMutation();
  virtual Individual* mutate(Individual* individual);
};

#endif
