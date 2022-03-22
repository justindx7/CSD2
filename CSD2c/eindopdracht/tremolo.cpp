#include "tremolo.h"
#include "sine.h"

Tremolo::Tremolo(float drywet, bool bypass,unsigned int samplerate) :
Effect(drywet, bypass,samplerate)
{
  osc = new Sine(440,samplerate);
  cout << "Tremolo - Constructor " << endl;
}

Tremolo::~Tremolo()
{
  delete osc;
  osc = nullptr;
}

void setModFreq(float val)
{
  float modFreq = 0;
  val = modFreq;
}

float Tremolo::applyEffect(float sample)
{
  float modSig = (osc->genNextSample() + 1.0)*0.5;
  return sample * modSig;
}

void setParameter(string id, float val)
{
  if (id == "setModFreq")
  {
      std::cout << val << "\n";
      setModFreq(val);
  }
}
