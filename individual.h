#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include "array.h"
#include "fracture.h"

class Individual {
private:
  Fracture* fracture;
  float fitness;
public:
  Individual();
  ~Individual();
  void mutate();
  // sort methods
  Array<Individual*>* sortByHighestFitness(Array<Individual*>* list);
  Array<Individual*>* mergeByHighestFitness(Array<Individual*>* one,Array<Individual*>* two);
  Array<Individual*>* sortByLowestFitness(Array<Individual*>* list);
  Array<Individual*>* mergeByLowestFitness(Array<Individual*>* one,Array<Individual*>* two);
  // getter methods
  float getFitness();
  // setter methods
  void setFitness(float param);
};

#endif
