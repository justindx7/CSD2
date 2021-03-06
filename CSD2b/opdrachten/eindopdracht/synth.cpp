#include "synth.h"

double Synth::samplerate = 0;

Synth::Synth(float midiPitch) : midiPitch(midiPitch)
{
}

Synth::~Synth()
{
  std::cout << "Synth - destructor\n";
}

double Synth::midiToFrequency(float pitch)
{
  // turns midi note into frequency
  return pow(2.0, (float(pitch) - 69.0) / 12.0) * 440.0;
}

double Synth::getSampleRate()
{
  return samplerate;
}

void Synth::setSampleRate(double newSamplerate)
{
  samplerate = newSamplerate;
}

void Synth::setSample(double newSample)
{
  sample = newSample;
}

void Synth::setMidiPitch(float pitch)
{

  midiPitch = pitch;
  updateFrequency(midiToFrequency(midiPitch));

}

double Synth::getSample()
{
  return sample;
}

void Synth::tick()
{
  calculate();
}