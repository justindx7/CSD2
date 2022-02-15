#include "effect.h" 

Effect::Effect(float drywet, bool bypass, unsigned int samplerate)
: drywet(drywet), bypass(bypass)
{
}
Effect::~Effect()
{
}
float Effect::processFrame(float sample)
{
    return (bypass) ? sample : process(sample);
}

// virtual tick do nothing if not overriden
void Effect::tick(){}


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