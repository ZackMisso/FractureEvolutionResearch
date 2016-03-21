#ifndef __PROGRAMDATA_H__
#define __PROGRAMDATA_H__

#include "globalInclude.h"
#include "array.h"
#include "fracture.h"

class ProgramData {
private:
  Array<Fracture*>* storedFractures;
  Fracture* currentFracture;
public:
  ProgramData();
  ~ProgramData();
  void save();
  void load();
  void createNewFracture();
  // getter methods
  Array<Fracture*>* getStoredFractures();
  Fracture* getCurrentFracture();
  // setter methods
  void setStoredFractures(Array<Fracture*>* param);
  void setCurrentFracture(Fracture* param);
};

#endif
