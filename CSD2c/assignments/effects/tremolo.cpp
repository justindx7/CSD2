#include "sine.h"
#include "tremolo.h"

Tremolo::Tremolo(float freq, float drywet, bool bypass, unsigned int samplerate) 
: Effect(drywet, bypass, samplerate)

{
osc = new Sine(freq, samplerate);
}

Tremolo::~Tremolo()
{
    delete osc;
    osc = nullptr;
}

void Tremolo::setModFreq(float freq)
{
  osc->setFrequency(freq);
}

float Tremolo::process(float sample)
{
  modSignal = (osc->genNextSample() + 1.0f) * 0.5f;
 return  sample * modSignal;
}