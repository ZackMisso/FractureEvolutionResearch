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
