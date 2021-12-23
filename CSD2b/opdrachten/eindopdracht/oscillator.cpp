#include "oscillator.h"
#include "synth.h"

Oscillator::Oscillator(float frequency, double amplitude)
    : frequency(frequency), amplitude(amplitude)
{
}

Oscillator::~Oscillator()
{
  std::cout << "Oscillator - destructor\n";
}

void Oscillator::setFrequency(float newFrequency)
{
  frequency = newFrequency;
}

float Oscillator::getFrequency()
{
  return frequency;
}

double Oscillator::getSampleRate()
{
  return Synth::getSampleRate();
}

void Oscillator::setSample(float newSample)
{
  sample = newSample;
}

float Oscillator::getSample()
{
  return sample;
}

float Oscillator::getAmplitude()
{
  return amplitude;
}

//make a sample
void Oscillator::tick()
{
  phase += getFrequency() / getSampleRate();
  // wrap the phase so it stays in the interval [0, 1]
  if (phase > 1)
    phase -= 1.0;
  calcNextSample();
  sample *= amplitude;
}
