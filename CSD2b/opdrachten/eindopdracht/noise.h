#ifndef _NOISE_H_
#define _NOISE_H_
#include <iostream>
#include "oscillator.h"

class Noise : public Oscillator
{
public:
  //Constructor and destructor
  Noise();
  Noise(float frequency, double amplitude);
  ~Noise();

//calculate wave form
  void calcNextSample() override;
};

#endif
