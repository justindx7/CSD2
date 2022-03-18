#ifndef _NOISE_H_
#define _NOISE_H_
#include <iostream>
#include "oscillator.h"

class Noise : public Oscillator
{
public:
  //Constructor and destructor
  Noise();
  Noise(float frequency, float samplerate);
  ~Noise();

private:
  // calculate the next sample according to sine calculation
  void calcNextSample() override;
};

#endif
