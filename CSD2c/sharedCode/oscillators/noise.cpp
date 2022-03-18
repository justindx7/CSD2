#include "noise.h"
#include "math.h"


Noise::Noise() : Noise(0, 0)
{}

Noise::Noise(float frequency, float samplerate) :
  Oscillator(frequency, samplerate) {}

Noise::~Noise() {}

void Noise::calcNextSample()
{
  float rnd =rand() % 100;
  rnd = rnd/100;
  sample = rnd;
  // TODO - move to base class
  sample *= amplitude;
}
