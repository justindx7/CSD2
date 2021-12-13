#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include "oscillator.h"

class Square : public Oscillator
{
public:
  //Constructor and destructor
  Square();
  Square(float frequency, double amplitude);
  ~Square();

  //calculate waveform
  void calcNextSample() override;
};

#endif
