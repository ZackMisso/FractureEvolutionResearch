#ifndef __EDGECONSTRAINT_H__
#define __EDGECONSTRAINT_H__

#include "edge.h"

class EdgeConstraint {
private:
public:
  EdgeConstraint();
  ~EdgeConstraint();
  virtual bool meetsConstraint(Edge* edge);
};

#endif
