#include "individual.h"

Individual::Individual() {
  fitness = 0.0f;
}

Individual::~Individual() {
  // to be implemented
}

Array<Individual*>* Individual::sortByHighestFitness(Array<Individual*>* list) {
  // to be implemented
  return 0x0;
}

Array<Individual*>* Individual::mergeByHighestFitness(Array<Individual*>* one,Array<Individual*>* two) {
  // to be implemented
  return 0x0;
}

Array<Individual*>* sortByLowestFitness(Array<Individual*>* list) {
  // to be implemented
  return 0x0;
}

Array<Individual*>* mergeByLowestFitness(Array<Individual*>* one,Array<Individual*>* two) {
  // to be implemented
  return 0x0;
}

float Individual::getFitness() { return fitness; }

void Individual::setFitness(float param) { fitness = param; }
