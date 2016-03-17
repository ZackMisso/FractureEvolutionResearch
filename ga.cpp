#include "ga.h"

GA::GA() {
  individuals = new Array<Individual*>();
  hallOfFame = new Array<Individual*>();
  fitFunction = new FitnessFunction();
  numberOfGenerations = 100;
}

GA::~GA() {
  while(individuals->getSize())
    delete individuals->removeLast();
  while(hallOfFame->getSize())
    delete individuals->removeLast();
  delete individuals;
  delete hallOfFame;
  delete fitFunction;
}

void GA::simulateEvolution() {
  // to be implemented
}

void GA::simulateGeneration() {
  // to be implemented
}

void GA::writeEvolutionState(string file) {
  // to be implemented
}

void GA::readEvolutionState(string file) {
  // to be implemented
}

Array<Individual*>* GA::getIndividuals() { return individuals; }
Array<Individual*>* GA::getHallOfFame() { return hallOfFame; }
FitnessFunction* GA::getFitnessFunction() { return fitFunction; }
int GA::getNumberOfGenerations() { return numberOfGenerations; }

void GA::setIndividuals(Array<Individual*>* param) { individuals = param; }
void GA::setHallOfFame(Array<Individual*>* param) { hallOfFame = param; }
void GA::setFitnessFunction(FitnessFunction* param) { fitFunction = param; }
void GA::setNumberOfGenerations(int param) { numberOfGenerations = param; }
