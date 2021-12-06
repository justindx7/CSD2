#include "square.h"
#include "math.h"

//signum function 
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Square::Square(float frequency, double samplerate) 
  : Oscillator(frequency, samplerate)
{
  std::cout << "Square - constructor\n";
}

Square::~Square() 
{
  std::cout << "Square - destructor\n";
}

float Square::getSample() 
{
  return sample;
}

void Square::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  // NOTE 2. - still need todo 'something' with the phase, see 04_sin_function
  phase += getFrequency() / getSampleRate();
  sample = sgn(sin(M_PI * 2 * phase) * amplitude);
}

