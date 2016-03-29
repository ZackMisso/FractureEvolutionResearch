#include "vertPositionMutation.h"

VertPositionMutation::VertPositionMutation() { }

VertPositionMutation::VertPositionMutation(real param) : MutationFunction(param) { }

VertPositionMutation::~VertPositionMutation() { }

Individual* VertPositionMutation::mutate(Individual* individual) {
  Fracture* copy = individual->getFracture()->copy();
  Individual* newIndividual = new Individual(mutate(copy));
  return newIndividual;
}

Fracture* VertPositionMutation::mutate(Fracture* fracture) {
  // to be implemented or extended
  return fracture;
}
