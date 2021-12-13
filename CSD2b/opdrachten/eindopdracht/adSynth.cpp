#include "adSynth.h"
#include <math.h>
#include "sine.h"
#include "square.h"
#include "saw.h"

//function create oscillators
std::vector<Oscillator*> AdSynth::createOscillators(float frequency, double amplitude)
{
  float freqRatios [] = {0.56, 1.56,0.92,2.62,1.19,1.7,2.0,2.74,3.0, 3.7,4.07};
  //TODO write for loop and array to automaticaly set freq and amp for each osc
  std::vector<Oscillator*> oscillators;
for(int i= 0; i < 10; i++)
{
  oscillators.push_back(new Square(frequency * freqRatios[i],  amplitude / (i + 1)));
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