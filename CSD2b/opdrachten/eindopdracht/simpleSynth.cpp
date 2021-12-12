#include "simpleSynth.h"
#include <math.h>
#include "sine.h"
#include "square.h"
#include "saw.h"


SimpleSynth::SimpleSynth(float midiPitch, Oscillator* oscillator)
    : Synth(midiPitch), oscillator(oscillator)
{
  setMidiPitch(midiPitch);
}

SimpleSynth::~SimpleSynth()
{
  delete oscillator;
  std::cout << "simpleSynth - destructor\n";
}

void SimpleSynth::tick()
{
    oscillator->tick();
}

void SimpleSynth::setMidiPitch(float midiPitch)
{
  // TODO check if pitch is different
  // TODO - check if pitch is in range
  double freq = midiToFrequency(midiPitch);

    oscillator->setFrequency(freq);
}

