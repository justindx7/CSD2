#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, double amplitude) 
  : Oscillator(frequency, amplitude)
{
  std::cout << "Saw - constructor\n";
}

Saw::~Saw() 
{
  std::cout << "Saw - destructor\n";
}

void Saw::calcNextSample()
{
  // calculate saw wave
  setSample(phase * 2.0 - 1.0);
}
