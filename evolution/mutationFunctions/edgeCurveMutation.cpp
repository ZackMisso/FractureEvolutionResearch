#include "edgeCurveMutation.h"

EdgeCurveMutation::EdgeCurveMutation() { }

EdgeCurveMutation::EdgeCurveMutation(real param) : MutationFunction(param) { }

EdgeCurveMutation::~EdgeCurveMutation() { }

Individual* EdgeCurveMutation::mutate(Individual* individual) {
  // to be implemented
  return 0x0;
}

Fracture* EdgeCurveMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
