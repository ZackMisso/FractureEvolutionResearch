#include "fitnessFunction.h"

FitnessFunction::FitnessFunction() {
  // to be implemented
}

FitnessFunction::~FitnessFunction() {
  // to be implemented
}

void FitnessFunction::preProcess(Array<Individual*>* individuals) {
  // to be extended
}

float FitnessFunction::getFitness(Individual* individual) {
  // to be implemented or extended
  return 0.0f;
}
