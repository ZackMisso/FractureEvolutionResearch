#include "evolutionSettings.h"

EvolutionSettings* EvolutionSettings::instance = 0x0;

EvolutionSettings::EvolutionSettings() {
  init();
}

EvolutionSettings::~EvolutionSettings() { }

EvolutionSettings* EvolutionSettings::getInstance() {
  return instance;
}

void EvolutionSettings::init() {
  maxMovePercent = 0.05;
  distBeforeJump = 0.03;
}

void EvolutionSettings::initialize() {
  if(!instance)
    instance = new EvolutionSettings();
}

void EvolutionSettings::destroy() {
  if(instance)
    delete instance;
}

real EvolutionSettings::getMaxMovePercent() { return maxMovePercent; }
real EvolutionSettings::getDistBeforeJump() { return distBeforeJump; }

void EvolutionSettings::setMaxMovePercent(real param) { maxMovePercent = param; }
void EvolutionSettings::setDistBeforeJump(real param) { distBeforeJump = param; }
