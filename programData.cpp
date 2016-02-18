#include "programData.h"

ProgramData::ProgramData() {
  storedFractures = new Array<Fracture*>();
  currentFracture = new Fracture();
}

ProgramData::~ProgramData() {
  delete currentFracture;
  while(storedFractures->getSize())
    delete storedFractures->removeLast();
}

void ProgramData::save() {
  // to be implemented
}

void ProgramData::load() {
  // to be implemented
}

void ProgramData::createNewFracture() {
  // to be implemented
}

Array<Fracture*>* ProgramData::getStoredFractures() { return storedFractures; }
Fracture* ProgramData::getCurrentFracture() { return currentFracture; }

void ProgramData::setStoredFractures(Array<Fracture*>* param) { storedFractures = param; }
void ProgramData::setCurrentFracture(Fracture* param) { currentFracture = param; }
