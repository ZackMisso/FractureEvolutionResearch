#include "intVoidMap.h"

IntVoidMap::IntVoidMap(void* v,int k) {
  val = v;
  key = k;
}

IntVoidMap::~IntVoidMap() { }

Array<IntVoidMap*>* IntVoidMap::sort(Array<IntVoidMap*>* list) {
  if(list->getSize()<=1)
    return list;
  Array<IntVoidMap*>* one = new Array<IntVoidMap*>();
  Array<IntVoidMap*>* two = new Array<IntVoidMap*>();
  int i=0;
  for(;i<list->getSize()/2;i++)
    one->add(list->get(i));
  for(;i<list->getSize();i++)
    two->add(list->get(i));
  while(list->getSize())
    list->removeLast();
  delete list;
  return merge(sort(one),sort(two));
}

Array<IntVoidMap*>* IntVoidMap::merge(Array<IntVoidMap*>* one,Array<IntVoidMap*>* two) {
  Array<IntVoidMap*>* sorted = new Array<IntVoidMap*>();
  int i=0;
  int j=0;
  while(i != one->getSize() && j != two->getSize()) {
    if(one->get(i)->getKey() > two->get(j)->getKey())
      sorted->add(two->get(j++));
    else
      sorted->add(one->get(i++));
  }
  while(i != one->getSize())
    sorted->add(one->get(i++));
  while(j != two->getSize())
    sorted->add(two->get(j++));
  while(one->getSize())
    one->removeLast();
  while(two->getSize())
    two->removeLast();
  delete one;
  delete two;
  return sorted;
}

void* IntVoidMap::getVal() { return val; }
int IntVoidMap::getKey() { return key; }

void IntVoidMap::setVal(void* param) { val = param; }
void IntVoidMap::setKey(int param) { key = param; }
