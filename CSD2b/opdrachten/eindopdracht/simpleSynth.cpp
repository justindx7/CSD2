#include "simpleSynth.h"
#include <math.h>
#include "saw.h"


SimpleSynth::SimpleSynth(float midiPitch)
    : Synth(midiPitch), saw(midiToFrequency(midiPitch), 1.0)
{
}

SimpleSynth::~SimpleSynth()
{
  std::cout << "simpleSynth - destructor\n";
}

void SimpleSynth::calculate()
{
  saw.tick();
 setSample(saw.getSample());

}
void SimpleSynth::updateFrequency(double freq)
{
  saw.setFrequency(freq);
}

