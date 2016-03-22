#ifndef __VERTCONSTRAINT_H__
#define __VERTCONSTRAINT_H__

#include "../../globalInclude.h"
#include "../../geometry/vertex.h"

class VertConstraint {
private:
public:
  VertConstraint();
  ~VertConstraint();
  virtual bool meetsConstraint(Vertex* vert);
};

#endif
