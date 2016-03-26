#include "individual.h"

Individual::Individual() {
  fracture = new Fracture();
  fitness = 0.0f;
  id = -1;
}

Individual::Individual(int param) {
  fracture = new Fracture();
  fitness = 0.0;
  id = param;
}

Individual::~Individual() {
  delete fracture;
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

real Individual::getFitness() { return fitness; }
Fracture* Individual::getFracture() { return fracture; }
int Individual::getID() { return id; }

void Individual::setFitness(real param) { fitness = param; }
void Individual::setFracture(Fracture* param) { fracture = param; }
void Individual::setID(int param) { id=param; }
