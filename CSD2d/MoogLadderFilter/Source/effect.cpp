/*
  ==============================================================================

    effect.cpp
    Created: 1 Jun 2022 12:42:23am
    Author:  Justin Bonnet

  ==============================================================================
*/

#include "effect.h"

Effect::Effect(float drywet, bool bypass)
: drywet(drywet), bypass(bypass)
{
}
Effect::~Effect()
{
}
float Effect::process(float sample)
{
    float output;
    //DRYWET
    output = applyEffect(sample);
    output *= getDrywet();
    output += sample + 1.0 - getDrywet();
    //if bypass true return the input sample if bypass false return the output.
    return (bypass) ? sample : output;
}
void Effect::setDrywet(float _drywet)
{
    drywet = _drywet;
}
float Effect::getDrywet(){
    return drywet;
}

void Effect::setBypass(bool _bypass)
{
    bypass = _bypass;
}

bool Effect::getBypass()
{
 return bypass;
}

void Effect::setSamplerate(unsigned int _samplerate)
{
    samplerate = _samplerate;
    DBG(samplerate);
}
