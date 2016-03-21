#include "crossoverFunction.h"

CrossoverFunction::CrossoverFunction() {
  probability = 0x0;
}

CrossoverFunction::CrossoverFunction(real param) {
  probability = param;
}

CrossoverFunction::~CrossoverFunction() {
  // does nothing for now
}

Individual* CrossoverFunction::crossover(Individual* one,Individual* two) {
  // to be implemented or extended
  return one;
}

real CrossoverFunction::getProbability() { return probability; }

void CrossoverFunction::setProbability(real param) { probability = param; }
