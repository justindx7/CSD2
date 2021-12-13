#ifndef _SAW_H_
#define _SAW_H_
#include <iostream>
#include "oscillator.h"

class Saw : public Oscillator
{
public:
  //Constructor and destructor
  Saw();
  Saw(float frequency, double amplitude);
  ~Saw();

//calculate wave form
  void calcNextSample() override;
};

#endif
