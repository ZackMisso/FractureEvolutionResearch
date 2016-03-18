#include "individual.h"

Individual::Individual() {
  fitness = 0.0f;
}

Individual::~Individual() {
  // to be implemented
}

void Individual::mutate() {
  // to be implemented
}

Array<Individual*>* Individual::sortByHighestFitness(Array<Individual*>* list) {
  //Array<Individual*>* sorted = new Array<Individual*>();
  if(list->getSize()==1)
    return list;
  Array<Individual*>* one = new Array<Individual*>();
  Array<Individual*>* two = new Array<Individual*>();
  int i=0;
  for(;i<list->getSize()/2;i++)
    one->add(list->removeLast());
  for(;i<list->getSize();i++)
    two->add(list->removeLast());
  return mergeByHighestFitness(sortByHighestFitness(one),sortByHighestFitness(two));
}

Array<Individual*>* Individual::mergeByHighestFitness(Array<Individual*>* one,Array<Individual*>* two) {
  Array<Individual*>* sorted = new Array<Individual*>();
  while(one->getSize() && two->getSize()) {
    if(one->get(0)->getFitness() > two->get(0)->getFitness())
      sorted->add(one->remove(0));
    else
      sorted->add(two->remove(0));
  }
  // NEED TO FIX INEFFICIENCIES IN ARRAY
  while(one->getSize())
    sorted->add(one->remove(0));
  while(two->getSize())
    sorted->add(two->remove(0));
  delete one;
  delete two;
  return sorted;
}

Array<Individual*>* Individual::sortByLowestFitness(Array<Individual*>* list) {
  if(list->getSize()==1)
    return list;
  Array<Individual*>* one = new Array<Individual*>();
  Array<Individual*>* two = new Array<Individual*>();
  int i=0;
  for(;i<list->getSize()/2;i++)
    one->add(list->removeLast());
  for(;i<list->getSize();i++)
    two->add(list->removeLast());
  return mergeByHighestFitness(sortByHighestFitness(one),sortByHighestFitness(two));
}

Array<Individual*>* Individual::mergeByLowestFitness(Array<Individual*>* one,Array<Individual*>* two) {
  Array<Individual*>* sorted = new Array<Individual*>();
  while(one->getSize() && two->getSize()) {
    if(one->get(0)->getFitness() < two->get(0)->getFitness())
      sorted->add(one->remove(0));
    else
      sorted->add(two->remove(0));
  }
  // NEED TO FIX INEFFICIENCIES IN ARRAY
  while(one->getSize())
    sorted->add(one->remove(0));
  while(two->getSize())
    sorted->add(two->remove(0));
  delete one;
  delete two;
  return sorted;
}

float Individual::getFitness() { return fitness; }

void Individual::setFitness(float param) { fitness = param; }
