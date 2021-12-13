#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, double amplitude) 
  : Oscillator(frequency, amplitude)
{
  std::cout << "Sine - constructor\n";
}

Sine::~Sine() 
{
  std::cout << "Sine - destructor\n";
}

void Sine::calcNextSample() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  // NOTE 2. - still need todo 'something' with the phase, see 04_sin_function
  setSample(sin(M_PI * 2 * phase));
}

