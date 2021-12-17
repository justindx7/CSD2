#include "adSynth.h"
#include <math.h>
#include "sine.h"

//function create oscillators
std::vector<Oscillator *> AdSynth::createOscillators(float frequency, double amplitude)
{
  // write for loop and array to automaticaly set freq and amp for each osc

  std::vector<Oscillator *> oscillators;
  for (int i = 0; i < 10; i++)
  {
    oscillators.push_back(new Sine(frequency * freqRatios[i], amplitude / (i + 1)));
  }
  return oscillators;
}

AdSynth::AdSynth(float midiPitch)
    // call createOscillators and turn the midi pitch into frequency
    : Synth(midiPitch), oscillators(createOscillators(midiToFrequency(midiPitch), 1.0))
{
}

AdSynth::~AdSynth()
{
  // destroy oscillators
  for (auto osc : oscillators)
  {
    delete osc;
  }
  std::cout << "AdSynth - destructor\n";
}

void AdSynth::calculate()
{
  float sample = 0.0;
  for (auto osc : oscillators)
  {
    osc->tick();
    //amplitudes gets divided by the amount of oscillators so the amps dont stack up
    sample += osc->getSample() * osc->getAmplitude() / oscillators.size();
  }
  setSample(sample);
}
void AdSynth::updateFrequency(double freq)
{
  int i = 0;
  for (auto osc : oscillators)
  {
    osc->setFrequency(freq * freqRatios[i]);
    i++;
  }
}
