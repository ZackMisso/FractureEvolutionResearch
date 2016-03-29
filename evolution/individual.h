#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "../geometry/fracture.h"

class Individual {
private:
  Fracture* fracture;
  real fitness;
  int id; // maybe
public:
  Individual();
  Individual(int param);
  Individual(Fracture* fract);
  Individual(int param,Fracture* fract);
  ~Individual();
  // sort methods
  static Array<Individual*>* sortByHighestFitness(Array<Individual*>* list);
  static Array<Individual*>* mergeByHighestFitness(Array<Individual*>* one,Array<Individual*>* two);
  static Array<Individual*>* sortByLowestFitness(Array<Individual*>* list);
  static Array<Individual*>* mergeByLowestFitness(Array<Individual*>* one,Array<Individual*>* two);
  // getter methods
  real getFitness();
  Fracture* getFracture();
  int getID();
  // setter methods
  void setFitness(real param);
  void setFracture(Fracture* fracture);
  void setID(int param);
};

#endif
