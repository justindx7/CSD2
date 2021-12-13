#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include "oscillator.h"

class Sine : public Oscillator
{
public:
  //Constructor and destructor
  Sine(float frequency, double amplitude);
  ~Sine();

  // calculate waveform
private:
  void calcNextSample() override;
};

#endif
