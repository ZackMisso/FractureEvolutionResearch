#ifndef __VERTPOSITIONMUTATION_H__
#define __VERTPOSITIONMUTATION_H__

#include "../../globalInclude.h"
#include "mutationFunction.h"

class VertPositionMutation : public MutationFunction {
private:
public:
  VertPositionMutation();
  VertPositionMutation(real param);
  ~VertPositionMutation();
  Individual* mutate(Individual* individual);
};

#endif
