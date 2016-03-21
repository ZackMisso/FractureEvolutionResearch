#ifndef __ADDRANDOMEDGEMUTATION_H__
#define __ADDRANDOMEDGEMUTATION_H__

#include "globalInclude.h"
#include "mutationFunction.h"

class AddRandomEdgeMutation : public MutationFunction {
private:
public:
  AddRandomEdgeMutation();
  AddRandomEdgeMutation(real param);
  ~AddRandomEdgeMutation();
  virtual Individual* mutate(Individual* individual);
};

#endif
