#include "oscillator.h"

Oscillator::Oscillator(float frequency, double samplerate) 
  : frequency(frequency), samplerate(samplerate)
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

void Oscillator::setSampleRate(double newSamplerate)
{
  // TODO add check to see if parameter is valid
  samplerate = newSamplerate;
}

double Oscillator::getSampleRate()
{
  return samplerate;
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
