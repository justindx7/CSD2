#include "saw.h"
#include "math.h"

Saw::Saw(float frequency) 
  : Oscillator(frequency)
{
  std::cout << "Saw - constructor\n";
}

Saw::~Saw() 
{
  std::cout << "Saw - destructor\n";
}

void Saw::calculate()
{
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  // NOTE 2. - still need todo 'something' with the phase, see 04_sin_function
  phase += getFrequency() / getSampleRate();
  if (phase > 1)
    phase -= 1.0;
  // calculate saw wave
  setSample(phase * 2.0 - 1.0);
  setSample(getSample() * amplitude);
}