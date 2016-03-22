#ifndef __ADDRANDOMVERTMUTATION_H__
#define __ADDRANDOMVERTMUTATION_H__

#include "../../globalInclude.h"
#include "mutationFunction.h"

class AddRandomVertMutation : public MutationFunction {
private:
public:
  AddRandomVertMutation();
  AddRandomVertMutation(real param);
  ~AddRandomVertMutation();
  virtual Individual* mutate(Individual* individual);
};

#endif
