#include "noiseSynth.h"
#include <math.h>


NoiseSynth::NoiseSynth(float midiPitch)
    : Synth(midiPitch), noise(midiToFrequency(midiPitch), 1.0)
{
}

NoiseSynth::~NoiseSynth()
{
  std::cout << "noiseSynth - destructor\n";
}

void NoiseSynth::calculate()
{
 noise.tick();
 setSample(noise.getSample());

}
void NoiseSynth::updateFrequency(double freq)
{
  noise.setFrequency(freq);
}

