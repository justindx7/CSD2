#ifndef _SAW_H_
#define _SAW_H_
#include <iostream>
#include "oscillator.h"

class Saw : public Oscillator
{
public:
  //Constructor and destructor
  Saw(float frequency, double samplerate);
  ~Saw();

//calculate wave form
  void calculate() override;

private:
  float amplitude = 1.0;
  float phase = 0;
};

#endif
