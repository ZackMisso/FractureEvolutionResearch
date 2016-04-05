#ifndef __EVOLUTIONSETTINGS_H__
#define __EVOLUTIONSETTINGS_H__

#include "../globalInclude.h"

class EvolutionSettings {
private:
  static EvolutionSettings* instance;
  real maxMovePercent;
  real distBeforeJump;
  EvolutionSettings();
public:
  ~EvolutionSettings();
  void init();
  static EvolutionSettings* getInstance();
  static void initialize();
  static void destroy();
  // getter methods
  real getMaxMovePercent();
  real getDistBeforeJump();
  // setter methods
  void setMaxMovePercent(real param);
  void setDistBeforeJump(real param);
};

#endif
