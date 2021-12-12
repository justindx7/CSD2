#include "sine.h"
#include "math.h"

Sine::Sine(float frequency) 
  : Oscillator(frequency)
{
  std::cout << "Sine - constructor\n";
}

Sine::~Sine() 
{
  std::cout << "Sine - destructor\n";
}

void Sine::calculate() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  // NOTE 2. - still need todo 'something' with the phase, see 04_sin_function
  phase += getFrequency() / getSampleRate();
  setSample(sin(M_PI * 2 * phase) * amplitude);
}

