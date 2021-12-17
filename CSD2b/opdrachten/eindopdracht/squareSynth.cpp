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
  oscillators.push_back(new Square(frequency - 5, amplitude));
  oscillators.push_back(new Square(frequency + 5,amplitude));
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
    osc = nullptr;
  }
  std::cout << "SquareSynth - destructor\n";
}


void SquareSynth::calculate()
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

void SquareSynth::updateFrequency(double freq){
  int i = 0;
  for (auto osc : oscillators){
    osc->setFrequency(freq + detune[i]);
    i++;
  } 
}
