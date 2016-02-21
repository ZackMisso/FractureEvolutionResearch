#include "rng.h"
#include <stdlib.h>

float RNG::RandomFloat() {
  return static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}

float RNG::RandomFloat(int start,int stop) {
  int dist = stop-start;
  return RandomFloat()*dist + start;
}

float RNG::RandomFloat(float start,float stop) {
  float dist = stop-start;
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