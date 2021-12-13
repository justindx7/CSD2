#include "simpleSynth.h"
#include <math.h>
#include "sine.h"
#include "square.h"
#include "saw.h"


SimpleSynth::SimpleSynth(float midiPitch)
    : Synth(midiPitch), sine(midiToFrequency(midiPitch), 1.0)
{
}

SimpleSynth::~SimpleSynth()
{
  std::cout << "simpleSynth - destructor\n";
}

void SimpleSynth::calculate()
{
  sine.tick();
 setSample(sine.getSample());

}

