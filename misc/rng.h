#ifndef __RNG_H__
#define __RNG_H__

#include "../globalInclude.h"

class RNG {
public:
  static real RandomFloat();
  static real RandomFloat(real max);
  static real RandomFloat(int start,int stop);
  static real RandomFloat(real start,real stop);
  static real RandomFloatMin(real min);
  static real RandomFloatMinMax(real min,real max);
  static int RandomInt();
  static int RandomInt(int max);
  static int RandomInt(int min,int max);
  static int RandomInt(int min,int max,int num);
  static int RandomIntWithException(int max,int exe);
};

#endif
