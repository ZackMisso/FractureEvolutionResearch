#include "addRandomEdgeMutation.h"

AddRandomEdgeMutation::AddRandomEdgeMutation() { }

AddRandomEdgeMutation::AddRandomEdgeMutation(real param) : MutationFunction(param) { }

AddRandomEdgeMutation::~AddRandomEdgeMutation() { }

Individual* AddRandomEdgeMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* AddRandomEdgeMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
