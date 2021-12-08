#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include "oscillator.h"

class Sine : public Oscillator
{
public:
  //Constructor and destructor
  Sine(float frequency, double samplerate);
  ~Sine();

  // calculate waveform
  void calculate() override;

  //getters and setters

private:
  float amplitude = 1.0;
  float phase = 0;
  // sample contains the current sample
};

#endif
