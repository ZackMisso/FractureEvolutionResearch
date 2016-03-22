#ifndef __REMOVERANDOMEDGEMUTATION_H__
#define __REMOVERANDOMEDGEMUTATION_H__

#include "../../globalInclude.h"
#include "mutationFunction.h"

class RemoveRandomEdgeMutation : public MutationFunction {
private:
public:
  RemoveRandomEdgeMutation();
  RemoveRandomEdgeMutation(real param);
  ~RemoveRandomEdgeMutation();
  virtual Individual* mutate(Individual* individual);
};

#endif
