#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <iostream>
#include "oscillator.h"

class Triangle : public Oscillator
{
public:
  //Constructor and destructor
  Triangle();
  Triangle(float frequency, double amplitude);
  ~Triangle();

//calculate wave form
  void calcNextSample() override;
};

#endif
