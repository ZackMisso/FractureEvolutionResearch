#include "vertPositionMutation.h"

VertPositionMutation::VertPositionMutation() { }

VertPositionMutation::VertPositionMutation(real param) : MutationFunction(param) { }

VertPositionMutation::~VertPositionMutation() { }

Individual* VertPositionMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* VertPositionMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
