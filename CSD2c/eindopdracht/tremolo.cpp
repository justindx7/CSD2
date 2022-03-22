#include "tremolo.h"
#include "sine.h"

Tremolo::Tremolo(float drywet, bool bypass,unsigned int samplerate) :
// Effect(drywet, bypass,samplerate),
modSig(0)
{
  cout << "Tremolo - Constructor " << endl;
}

Tremolo::~Tremolo()
{}

// float Tremolo::applyEffect(float sample)
// {
  // return 0;
// }

// void setParameter(string id, float val)
// {}
