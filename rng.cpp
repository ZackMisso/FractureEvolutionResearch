#include "rng.h"
#include <stdlib.h>

real RNG::RandomFloat() {
  return static_cast<real>(rand())/static_cast<real>(RAND_MAX);
}

real RNG::RandomFloat(int start,int stop) {
  int dist = stop-start;
  return RandomFloat()*dist + start;
}

real RNG::RandomFloat(real start,real stop) {
  real dist = stop-start;
  return RandomFloat()*dist + start;
}

int RNG::RandomInt() {
  return rand();
}

int RNG::RandomInt(int max) {
  return rand() % max;
}

int RNG::RandomInt(int min,int max) {
  int dist = max-min;
  return (rand() % dist) + min;
}

int RNG::RandomInt(int min,int max,int num) {
  if(max > num)
    return RandomInt(min,num);
  else
    return RandomInt(min,max);
}

int RNG::RandomIntWithException(int max,int exe) {
  int num=-1;
  while((num=RandomInt(max))==exe) {}
  return num;
}
