#include "chorus.h"
#include "circBuffer.h"
#include "triangle.h"
#include "sine.h"
#include "interpolation.h"

Chorus::Chorus(float drywet, bool bypass, unsigned int samplerate, float feedback, bool invertPolarity, float modFreq)
    : Effect(drywet, bypass, samplerate), invertPolarity(invertPolarity), feedback(feedback), modFreq(modFreq)
{
    circBuffer.resetSize(samplerate * 2);
    osc = new Sine(modFreq, samplerate);
}

Chorus::~Chorus()
{
    delete osc;
    osc = nullptr;
}

void Chorus::setModDepth(float val)
{
    // TODO check input
    modDepth = val;
}
void Chorus::setRate(float val)
{
    val = modFreq;
}

float Chorus::applyEffect(float sample)
{
    // modulation of delay time osc from 0 to 1 otherwise you would need an Delorean with flux capacitor
    LFO = (osc->genNextSample() + 1) * 0.5 * modDepth;
    circBuffer.setDistanceRW(LFO + offset);

    // feedback loop and bool to invert the polarity
    float val = (invertPolarity) ? sample + (modSample * feedback)
                                 : -sample + (modSample * feedback);
    circBuffer.write(val);

    float index = circBuffer.getDistanceRW();

    modSample = circBuffer.read();
    circBuffer.tick();
    return modSample;
}

void Chorus::setParameter(std::string id, float val)
{
    if (id == "modDepth")
    {
        std::cout << val << "\n";
        setModDepth(val);
    }
    if (id == "feedback")
    {
        setFeedback(val);
    }
    if (id == "polar")
    {
        setPolarity(val);
    }
    if(id =="freq"){
        osc->setFrequency(val);
    }
}

void Chorus::setFeedback(float _feedback)
{
    if (_feedback < 1)
    {
        feedback = _feedback;
    }
}

void Chorus::setPolarity(bool _invertPolarity)
{
    invertPolarity = _invertPolarity;
            std::cout << _invertPolarity << std::endl;
}
