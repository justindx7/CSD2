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
    float output;
    //DRYWET
    output = process(sample);
    output *= getDrywet();
    output += sample + 1.0 - getDrywet();
    
    return (bypass) ? sample : output;
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
// so you can change settings of all effects if not overriden do nothing
void Effect::setParameter(std::string id, float val){}