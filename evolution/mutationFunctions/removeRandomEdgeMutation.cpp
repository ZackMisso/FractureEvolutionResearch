#include "removeRandomEdgeMutation.h"

RemoveRandomEdgeMutation::RemoveRandomEdgeMutation() {
  // to be implemented
}

RemoveRandomEdgeMutation::RemoveRandomEdgeMutation(real param) : MutationFunction(param) {
  // to be implemented
}

RemoveRandomEdgeMutation::~RemoveRandomEdgeMutation() { }

Individual* RemoveRandomEdgeMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* RemoveRandomEdgeMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
