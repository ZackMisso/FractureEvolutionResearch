#ifndef __RNG_H__
#define __RNG_H__

class RNG {
public:
  static float RandomFloat();
  static float RandomFloat(int start,int stop);
  static float RandomFloat(float start,float stop);
  static int RandomInt();
  static int RandomInt(int max);
  static int RandomInt(int min,int max);
  static int RandomInt(int min,int max,int num);
};

#endif
