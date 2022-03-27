#include "tremolo.h"
#include "sine.h"
#include <string>

Tremolo::Tremolo(float drywet, bool bypass, unsigned int samplerate,float modFreq) :
Effect(drywet, bypass, samplerate)
{
  osc = new Sine(modFreq,samplerate);
}

Tremolo::~Tremolo()
{
  delete osc;
  osc = nullptr;
}

void Tremolo::setModFreq(float freq)
{
  freq = modFreq;
}

float Tremolo::applyEffect(float sample)
{
  float modSig = (osc->genNextSample() + 1.0)*0.5;
  return sample * modSig;
}

void Tremolo::setParameter(std::string id, float val)
{
  if (id == "ModFreq")
  {
      std::cout << val << "\n";
      setModFreq(val);
  }
}
