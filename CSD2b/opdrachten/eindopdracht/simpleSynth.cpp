#include "simpleSynth.h"
#include <math.h>
#include "saw.h"


SimpleSynth::SimpleSynth(float midiPitch)
    : Synth(midiPitch), triangle(midiToFrequency(midiPitch), 1.0)
{
}

SimpleSynth::~SimpleSynth()
{
  std::cout << "simpleSynth - destructor\n";
}

void SimpleSynth::calculate()
{
 triangle.tick();
 setSample(triangle.getSample());

}
void SimpleSynth::updateFrequency(double freq)
{
  triangle.setFrequency(freq);
}

