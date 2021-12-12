#include "simpleSynth.h"
#include <math.h>
#include "sine.h"
#include "square.h"
#include "saw.h"


SimpleSynth::SimpleSynth(float midiPitch, Oscillator* oscillator)
    : Synth(midiPitch), oscillator(oscillator)
{
}

SimpleSynth::~SimpleSynth()
{
  delete oscillator;
  std::cout << "simpleSynth - destructor\n";
}

void SimpleSynth::calc()
{
 double freq = midiToFrequency(midiPitch);

    oscillator->setFrequency(freq);
        oscillator->tick();
}



