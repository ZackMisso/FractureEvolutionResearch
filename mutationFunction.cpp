#include "mutationFunction.h"

MutationFunction::MutationFunction() {
  probability = 0.0;
}

MutationFunction::MutationFunction(real param) {
  probability = param;
}

MutationFunction::~MutationFunction() {
  // does nothing for now
}

Individual* MutationFunction::mutate(Individual* individual) {
  // to be implemented or extended
  return individual;
}

real MutationFunction::getProbability() { return probability; }

void MutationFunction::setProbability(real param) { probability = param; }
