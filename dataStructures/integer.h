#ifndef __INTEGER_H__
#define __INTEGER_H__

// This class is just to fix errors in using array

class Integer {
public:
  Integer() { val = 0; }
  Integer(int param) { val = param; }
  int val;
};

#endif
