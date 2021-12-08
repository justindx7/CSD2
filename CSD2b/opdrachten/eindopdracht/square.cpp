#include "square.h"
#include "math.h"


Square::Square(float frequency, double samplerate) 
  : Oscillator(frequency, samplerate)
{
  std::cout << "Square - constructor\n";
}

Square::~Square() 
{
  std::cout << "Square - destructor\n";
}

void Square::calculate() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += getFrequency() / getSampleRate();
  // wrap the phase so it stays in the interval [0, 1]
  if(phase > 1) phase -= 1.0;
  // square functionality comes here
  if(phase < 0.5) {
    setSample(1.0);
  } else {
    setSample(-1.0);
  }
  setSample(getSample() * amplitude);
}

