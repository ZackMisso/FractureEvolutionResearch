#include "removeRandomVertMutation.h"

RemoveRandomVertMutation::RemoveRandomVertMutation() { }

RemoveRandomVertMutation::RemoveRandomVertMutation(real param) : MutationFunction(param) { }

RemoveRandomVertMutation::~RemoveRandomVertMutation() { }

Individual* RemoveRandomVertMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* RemoveRandomVertMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
