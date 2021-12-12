#include "oscillator.h"

Oscillator::Oscillator(float frequency)
    : frequency(frequency)
{
}

Oscillator::~Oscillator()
{
  std::cout << "Oscillator - destructor\n";
}

//getters and setters
void Oscillator::setFrequency(float newFrequency)
{
  // TODO add check to see if parameter is valid
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

void Oscillator::tick()
{
  calculate();
}
