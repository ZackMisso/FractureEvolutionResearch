#ifndef __EDGECONSTRAINT_H__
#define __EDGECONSTRAINT_H__

#include "../../globalInclude.h"
#include "../../geometry/edge.h"

class EdgeConstraint {
private:
public:
  EdgeConstraint();
  ~EdgeConstraint();
  virtual bool meetsConstraint(Edge* edge);
};

#endif
