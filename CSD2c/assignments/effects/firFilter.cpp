#include "firFilter.h"
#include "sine.h"

FirFilter::FirFilter(float drywet, bool bypass, unsigned int samplerate)
: Effect(drywet, bypass, samplerate)
{
      osc = new Sine(0.8,samplerate);
 
}

FirFilter::~FirFilter()
{
}

float FirFilter::process(float sample)
{
  lfo = (osc->genNextSample() + 1) * 0.5; 
//eerste orde firfilter
 modSignal = history1 + (sample * 1 - lfo);
 history1 = sample * - lfo; 
  return modSignal;

// eerste oorde onepole filter
 // modSignal = (1 - feedback) * sample +  (feedback  * history1);
  //history1 = modSignal;
 // return modSignal;
}

void FirFilter::setParameter(std::string id, float val)
{
}

void FirFilter::tick()
{
}
