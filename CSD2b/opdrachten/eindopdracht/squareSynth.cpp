#include "squareSynth.h"
#include <math.h>
#include "sine.h"
#include "square.h"
#include "saw.h"

//function create oscillators
std::vector<Oscillator*> SquareSynth::createOscillators(float frequency, double amplitude)
{
  //TODO write for loop and array to automaticaly set freq and amp for each osc
  std::vector<Oscillator*> oscillators;
  oscillators.push_back(new Square(frequency - 20, amplitude));
  oscillators.push_back(new Square(frequency + 20,amplitude));
  return oscillators;
}

SquareSynth::SquareSynth(float midiPitch)
    // call createOscillators and turn the midi pitch into frequency
    : Synth(midiPitch), oscillators(createOscillators(midiToFrequency(midiPitch), 1.0))
{
}

SquareSynth::~SquareSynth()
{
  // destroy oscillators
  for (auto osc : oscillators)
  {
    delete osc;
  }
  std::cout << "SquareSynth - destructor\n";
}


void SquareSynth::calculate()
{
  float sample = 0.0;
  for (auto osc : oscillators)
  {
    osc->tick();
    sample += osc->getSample() * osc->getAmplitude() / oscillators.size();
  }
  setSample(sample);
}
