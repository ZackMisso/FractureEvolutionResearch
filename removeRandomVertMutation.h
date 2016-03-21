#ifndef __REMOVERANDOMVERTMUTATION_H__
#define __REMOVERANDOMVERTMUTATION_H__

#include "globalInclude.h"
#include "mutationFunction.h"

class RemoveRandomVertMutation : public MutationFunction {
private:
public:
  RemoveRandomVertMutation();
  RemoveRandomVertMutation(real param);
  ~RemoveRandomVertMutation();
  virtual Individual* mutate(Individual* individual);
};

#endif
