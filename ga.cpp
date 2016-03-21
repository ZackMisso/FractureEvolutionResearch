#include "ga.h"
#include "addRandomVertMutation.h"
#include "addRandomEdgeMutation.h"
#include "edgeCurveCrossover.h"
#include "edgeCurveMutation.h"
#include "removeRandomVertMutation.h"
#include "subAreaCrossover.h"
#include "vertPositionCrossover.h"
#include "vertPositionMutation.h"

GA::GA() {
  mutations = new Array<MutationFunction*>();
  crossovers = new Array<CrossoverFunction*>();
  individuals = new Array<Individual*>();
  hallOfFame = new Array<Individual*>();
  fitFunction = new FitnessFunction();
  numberOfGenerations = 100;
}

GA::~GA() {
  while(mutations->getSize())
    delete mutations->removeLast();
  while(crossovers->getSize())
    delete crossovers->removeLast();
  while(individuals->getSize())
    delete individuals->removeLast();
  while(hallOfFame->getSize())
    delete individuals->removeLast();
  delete individuals;
  delete hallOfFame;
  delete fitFunction;
}

void GA::initMutations() { // TODO :: Enter in the probabilities
  mutations->add(new AddRandomVertMutation(0.0));
  mutations->add(new AddRandomEdgeMutation(0.0));
  mutations->add(new EdgeCurveMutation(0.0));
  mutations->add(new RemoveRandomVertMutation(0.0));
  mutations->add(new VertPositionMutation(0.0));
}

void GA::initCrossovers() { // TODO :: Enter in the probabilities
  crossovers->add(new EdgeCurveCrossover(0.0));
  crossovers->add(new VertPositionCrossover(0.0));
  crossovers->add(new SubAreaCrossover(0.0));
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

Array<MutationFunction*>* GA::getMutations() { return mutations; }
Array<CrossoverFunction*>* GA::getCrossovers() { return crossovers; }
Array<Individual*>* GA::getIndividuals() { return individuals; }
Array<Individual*>* GA::getHallOfFame() { return hallOfFame; }
FitnessFunction* GA::getFitnessFunction() { return fitFunction; }
int GA::getNumberOfGenerations() { return numberOfGenerations; }

void GA::setMutations(Array<MutationFunction*>* param) { mutations = param; }
void GA::setCrossovers(Array<CrossoverFunction*>* param) { crossovers = param; }
void GA::setIndividuals(Array<Individual*>* param) { individuals = param; }
void GA::setHallOfFame(Array<Individual*>* param) { hallOfFame = param; }
void GA::setFitnessFunction(FitnessFunction* param) { fitFunction = param; }
void GA::setNumberOfGenerations(int param) { numberOfGenerations = param; }
