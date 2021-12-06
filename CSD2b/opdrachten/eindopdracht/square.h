#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include "oscillator.h"

class Square : public Oscillator
{
public:
  //Constructor and destructor
  Square(float frequency, double samplerate);
  ~Square();

  //return the current sample
  float getSample() override;
  // go to next sample
  void tick() override;

private:
  float amplitude = 1.0;
  float phase = 0;
  // sample contains the current sample
  float sample = 0;
};

#endif
