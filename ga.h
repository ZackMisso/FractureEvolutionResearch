#ifndef __GA_H__
#define __GA_H__

#include "globalInclude.h"
#include "array.h"
#include "individual.h"
#include "nn.h"
#include "fitnessFunction.h"
#include "mutationFunction.h"
#include "crossoverFunction.h"
#include "vertConstraint.h"
#include "edgeConstraint.h"
#include "faceConstraint.h"
#include "fractureConstraint.h"
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
  Array<Individual*>* individuals;
  Array<Individual*>* hallOfFame;
  FitnessFunction* fitFunction;
  int numberOfGenerations;
  void initMutations();
  void initCrossovers();
  void initVertConstraints();
  void initEdgeConstraints();
  void initFaceConstraints();
  void initFractureConstraints();
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
  Array<Individual*>* getIndividuals();
  Array<Individual*>* getHallOfFame();
  FitnessFunction* getFitnessFunction();
  int getNumberOfGenerations();
  // setter methods
  void setMutations(Array<MutationFunction*>* param);
  void setCrossovers(Array<CrossoverFunction*>* param);
  void setVertConstraints(Array<VertConstraint*>* param);
  void setEdgeConstraints(Array<EdgeConstraint*>* param);
  void setFaceConstraints(Array<FaceConstraint*>* param);
  void setFractureConstraints(Array<FractureConstraint*>* param);
  void setIndividuals(Array<Individual*>* param);
  void setHallOfFame(Array<Individual*>* param);
  void setFitnessFunction(FitnessFunction* param);
  void setNumberOfGenerations(int param);
};

#endif
