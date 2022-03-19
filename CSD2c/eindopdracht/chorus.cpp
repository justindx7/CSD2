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
    float index = sample;
    // modulation of delay time osc from 0 to 1 otherwise you would need an Delorean with flux capacitor
    LFO = (osc->genNextSample() + 1) * 0.5 * modDepth;
    circBuffer.setDistanceRW(LFO + offset);

    // feedback loop and bool to invert the polarity
    (invertPolarity) ? circBuffer.write(sample + (modSample * feedback))
                     : circBuffer.write((sample * -1) + (modSample * feedback));


    int i = (int)index;
    float indexDecimal = index - (float)i;
    //interpolation of the output buffer
    modSample = Interpolation::linMap(indexDecimal, circBuffer.read(), circBuffer.readNext());
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
}