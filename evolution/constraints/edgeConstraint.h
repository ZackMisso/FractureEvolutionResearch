#ifndef __EDGECONSTRAINT_H__
#define __EDGECONSTRAINT_H__

#include "../../globalInclude.h"
#include "constraint.h"
#include "../../geometry/edge.h"

class EdgeConstraint : public Constraint {
private:
public:
  EdgeConstraint();
  ~EdgeConstraint();
  virtual bool meetsConstraint(Edge* edge);
  virtual bool applyConstraint(Individual* individual);
};

#endif
