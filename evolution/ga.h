#ifndef __GA_H__
#define __GA_H__

#include "../globalInclude.h"
#include "../dataStructures/array.h"
#include "individual.h"
#include "nn.h"
#include "fitnessFunctions/fitnessFunction.h"
#include "mutationFunctions/mutationFunction.h"
#include "crossoverFunctions/crossoverFunction.h"
#include "constraints/vertConstraint.h"
#include "constraints/edgeConstraint.h"
#include "constraints/faceConstraint.h"
#include "constraints/fractureConstraint.h"
#include "penalty/penalty.h"
#include "../geometry/shapes/shape.h"
#include <string>

using namespace std;

class GA {
private:
  Array<MutationFunction*>* mutations;
  Array<CrossoverFunction*>* crossovers;
  Array<VertConstraint*>* vertConstraints;
  Array<EdgeConstraint*>* edgeConstraints;
  Array<FaceConstraint*>* faceConstraints;
  Array<FractureConstraint*>* fractureConstraints;
  Array<Penalty*>* penalties;
  Array<Individual*>* individuals;
  Array<Individual*>* hallOfFame;
  FitnessFunction* fitFunction;
  Shape* shape;
  int numberOfGenerations;
  int numberOfIndividuals;
  int nextIndividualID;
  void initMutations();
  void initCrossovers();
  void initVertConstraints();
  void initEdgeConstraints();
  void initFaceConstraints();
  void initFractureConstraints();
  void initPenalties();
  void initPopulation();
public:
  GA();
  ~GA();
  void simulateEvolution();
  void simulateGeneration();
  void writeEvolutionState(string file);
  void readEvolutionState(string file);
  // getter methods
  Array<MutationFunction*>* getMutations();
  Array<CrossoverFunction*>* getCrossovers();
  Array<VertConstraint*>* getVertConstraints();
  Array<EdgeConstraint*>* getEdgeConstraints();
  Array<FaceConstraint*>* getFaceConstraints();
  Array<FractureConstraint*>* getFractureConstraints();
  Array<Penalty*>* getPenalties();
  Array<Individual*>* getIndividuals();
  Array<Individual*>* getHallOfFame();
  FitnessFunction* getFitnessFunction();
  Shape* getShape();
  int getNumberOfGenerations();
  int getNumberOfIndividuals();
  int getNextIndividualID();
  // setter methods
  void setMutations(Array<MutationFunction*>* param);
  void setCrossovers(Array<CrossoverFunction*>* param);
  void setVertConstraints(Array<VertConstraint*>* param);
  void setEdgeConstraints(Array<EdgeConstraint*>* param);
  void setFaceConstraints(Array<FaceConstraint*>* param);
  void setFractureConstraints(Array<FractureConstraint*>* param);
  void setPenalties(Array<Penalty*>* param);
  void setIndividuals(Array<Individual*>* param);
  void setHallOfFame(Array<Individual*>* param);
  void setFitnessFunction(FitnessFunction* param);
  void setShape(Shape* param);
  void setNumberOfGenerations(int param);
  void setNumberOfIndividuals(int param);
  void setNextIndividualID(int param);
};

#endif
