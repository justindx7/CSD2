#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include "oscillator.h"

class Square : public Oscillator
{
public:
  //Constructor and destructor
  Square(float frequency);
  ~Square();

  //calculate waveform
  void calculate() override;

private:
  float amplitude = 1.0;
  float phase = 0;
};

#endif
