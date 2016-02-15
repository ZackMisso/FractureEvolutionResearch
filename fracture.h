#ifndef __FRACTURE_H__
#define __FRACTURE_H__

#include "array.h"

class Fracture {
private:
  Array<Vertex*> *verts;
  Array<Edge*> *edges; // will have multiple references
public:
  Fracture();
  ~Fracture();
};

#endif
