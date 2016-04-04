#ifndef __INTVOIDMAP_H__
#define __INTVOIDMAP_H__

#include "array.h"

class IntVoidMap {
private:
  void* val;
  int key;
public:
  IntVoidMap(void* v,int k);
  ~IntVoidMap();
  static Array<IntVoidMap*>* sort(Array<IntVoidMap*>* list);
  static Array<IntVoidMap*>* merge(Array<IntVoidMap*>* one,Array<IntVoidMap*>* two);
  // getter methods
  void* getVal();
  int getKey();
  // setter methods
  void setVal(void* param);
  void setKey(int param);
};

#endif
