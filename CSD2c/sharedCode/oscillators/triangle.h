#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <iostream>
#include "oscillator.h"

class Triangle : public Oscillator
{
public:
  //Constructor and destructor
  Triangle();
  Triangle(float frequency, float samplerate);
  ~Triangle();

private:
  // calculate the next sample according to sine calculation
  void calcNextSample() override;
};

#endif
