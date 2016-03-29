#ifndef __VERTCONSTRAINT_H__
#define __VERTCONSTRAINT_H__

#include "../../globalInclude.h"
#include "constraint.h"
#include "../../geometry/vertex.h"

class VertConstraint : public Constraint {
private:
public:
  VertConstraint();
  ~VertConstraint();
  virtual bool meetsConstraint(Vertex* vert);
  virtual bool applyConstraint(Individual* individual);
};

#endif
