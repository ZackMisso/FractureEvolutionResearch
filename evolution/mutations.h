#ifndef __MUTATIONS_H__
#define __MUTATIONS_H__

#include "../globalInclude.h"
#include "../geometry/fracture.h"

class Mutations {
public:
  static void AddRandomVertex(Fracture* fracture);
  static void RemoveRandomEdge(Fracture* fracture);
  static void BoxCrossOver(Fracture* one,Fracture* other);
};

#endif
