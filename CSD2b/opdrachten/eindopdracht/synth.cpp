#include "synth.h"
#include <math.h>

Synth::Synth(float midiPitch, double samplerate) 
{
  sine.setSampleRate(samplerate);
  setMidiPitch(midiPitch);
}

Synth::~Synth()
{
    std::cout << "Oscillator - destructor\n";

}

void Synth::tick()
{
  sine.tick();
  sample = sine.getSample();
}


double Synth::getSample()
{ 
 return sample; 
}

void Synth::setMidiPitch(float pitch)
{
  // TODO check if pitch is different
  // TODO - check if pitch is in range
  midiPitch = pitch;
  double freq = mtof(midiPitch);
  sine.setFrequency(freq);
}

double Synth::mtof(float pitch)
{
  // turns midi note into freq
  return pow(2.0, (float(pitch) - 69.0) / 12.0) * 440.0;
}
