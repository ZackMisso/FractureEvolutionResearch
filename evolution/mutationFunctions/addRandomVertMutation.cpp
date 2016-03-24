#include "addRandomVertMutation.h"

AddRandomVertMutation::AddRandomVertMutation() { }

AddRandomVertMutation::AddRandomVertMutation(real param) : MutationFunction(param) { }

AddRandomVertMutation::~AddRandomVertMutation() { }

Individual* AddRandomVertMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* AddRandomVertMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
