#include "ga.h"
#include "mutationFunctions/addRandomVertMutation.h"
#include "mutationFunctions/addRandomEdgeMutation.h"
#include "crossoverFunctions/edgeCurveCrossover.h"
#include "mutationFunctions/edgeCurveMutation.h"
#include "mutationFunctions/removeRandomVertMutation.h"
#include "crossoverFunctions/subAreaCrossover.h"
#include "crossoverFunctions/vertPositionCrossover.h"
#include "mutationFunctions/vertPositionMutation.h"

GA::GA() {
  mutations = new Array<MutationFunction*>();
  crossovers = new Array<CrossoverFunction*>();
  vertConstraints = new Array<VertConstraint*>();
  edgeConstraints = new Array<EdgeConstraint*>();
  faceConstraints = new Array<FaceConstraint*>();
  fractureConstraints = new Array<FractureConstraint*>();
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
  while(vertConstraints->getSize())
    delete vertConstraints->removeLast();
  while(edgeConstraints->getSize())
    delete edgeConstraints->removeLast();
  while(faceConstraints->getSize())
    delete faceConstraints->removeLast();
  while(fractureConstraints->getSize())
    delete fractureConstraints->removeLast();
  while(individuals->getSize())
    delete individuals->removeLast();
  while(hallOfFame->getSize())
    delete individuals->removeLast();
  delete mutations;
  delete crossovers;
  delete vertConstraints;
  delete edgeConstraints;
  delete faceConstraints;
  delete fractureConstraints;
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

void GA::initVertConstraints() {
  // to be implemented
}

void GA::initEdgeConstraints() {
  // to be implemented
}

void GA::initFaceConstraints() {
  // to be implemented
}

void GA::initFractureConstraints() {
  // to be implemented
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
Array<VertConstraint*>* GA::getVertConstraints() { return vertConstraints; }
Array<EdgeConstraint*>* GA::getEdgeConstraints() { return edgeConstraints; }
Array<FaceConstraint*>* GA::getFaceConstraints() { return faceConstraints; }
Array<FractureConstraint*>* GA::getFractureConstraints() { return fractureConstraints; }
Array<Individual*>* GA::getIndividuals() { return individuals; }
Array<Individual*>* GA::getHallOfFame() { return hallOfFame; }
FitnessFunction* GA::getFitnessFunction() { return fitFunction; }
int GA::getNumberOfGenerations() { return numberOfGenerations; }

void GA::setMutations(Array<MutationFunction*>* param) { mutations = param; }
void GA::setCrossovers(Array<CrossoverFunction*>* param) { crossovers = param; }
void GA::setVertConstraints(Array<VertConstraint*>* param) { vertConstraints = param; }
void GA::setEdgeConstraints(Array<EdgeConstraint*>* param) { edgeConstraints = param; }
void GA::setFaceConstraints(Array<FaceConstraint*>* param) { faceConstraints = param; }
void GA::setFractureConstraints(Array<FractureConstraint*>* param) { fractureConstraints = param; }
void GA::setIndividuals(Array<Individual*>* param) { individuals = param; }
void GA::setHallOfFame(Array<Individual*>* param) { hallOfFame = param; }
void GA::setFitnessFunction(FitnessFunction* param) { fitFunction = param; }
void GA::setNumberOfGenerations(int param) { numberOfGenerations = param; }