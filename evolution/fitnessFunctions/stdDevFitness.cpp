#include "stdDevFitness.h"
#include <cmath>

StdDevFitness::StdDevFitness() {
  //xBar = 0.0;
}

StdDevFitness::~StdDevFitness() {
  // to be implemented if needed
}

void StdDevFitness::preProcess(Array<Individual*>* individuals) {
  // implement if needed

  //xBar = 0.0;
  //for(int i=0;i<individuals->getSize();i++)
  //  xBar += individuals->get(i)->getFitness();
  //xBar /= individuals->getSize();
}

// INEFFICIENT FIX LATER
real StdDevFitness::getFitness(Individual* individual) {
  Array<Face*>* faces = individual->getFracture()->getFaces();
  real xBar = 0.0;
  for(int i=0;i<faces->getSize();i++)
    xBar += faces->get(i)->area();
  xBar /= faces->getSize();
  real stdDev = 0.0;
  for(int i=0;i<faces->getSize();i++)
    stdDev += (faces->get(i)->area() - xBar) * (faces->get(i)->area() - xBar);
  stdDev /= faces->getSize();
  return sqrt(stdDev);
}
