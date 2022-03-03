#include "chorus.h"
#include "circBuffer.h"
#include "triangle.h"
#include "sine.h"


Chorus::Chorus(float drywet, bool bypass, unsigned int samplerate,float feedback ,bool invertPolarity, float modFreq)
: Effect(drywet, bypass, samplerate), invertPolarity(invertPolarity), feedback(feedback), modFreq(modFreq)
{
    circBuffer.resetSize(samplerate * 2);
    osc = new Sine(modFreq,samplerate);
}

Chorus::~Chorus()
{
    delete osc;
    osc = nullptr;
}

void Chorus::setModDepth(float val)
{
    //TODO check input
    modDepth = val;
}
void Chorus::setRate(float val)
{
    val = modFreq;
}

float Chorus::process(float sample)
{
  //modulation of delay time osc from 0 to 1 otherwise you would need an Delorean with flux capacitor
    modSignal = (osc->genNextSample() + 1) * 0.5 * modDepth; 
    modSignal += 0.5;
    modSignal = (int)modSignal;
    circBuffer.setDistanceRW(modSignal + offset);

    float modSample = 0;
    //feedback loop and bool to invert the polarity
    (invertPolarity) ? circBuffer.write(sample + (modSample * feedback)) 
    : circBuffer.write((sample * -1) + (modSample * feedback));
    //TODO INTERPOLATIE
    modSample = circBuffer.read();

  return modSample;
}

void Chorus::setParameter(std::string id, float val)
{
    if(id == "modDepth")
    {
        std::cout << val << "\n";
        setModDepth(val);
    }
    if(id == "feedback")
    {
        setFeedback(val);
    }

}

void Chorus::tick()
{
    circBuffer.tick();
}

void Chorus::setFeedback(float _feedback)
{
    if(_feedback < 1)
    {
    feedback = _feedback;
    }
}

void Chorus::setPolarity(bool _invertPolarity)
{
     invertPolarity = _invertPolarity;
}