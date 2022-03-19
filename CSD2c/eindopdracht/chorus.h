#pragma once
#include <iostream>
#include "effect.h"
#include "oscillator.h"
#include "circBuffer.h"



class Chorus : public Effect
{  

public:
    Chorus(float drywet, bool bypass, 
    unsigned int samplerate, float feedback, bool invertPolarity, float modFreq);
    ~Chorus();
    float applyEffect(float sample) override;
    void setParameter(std::string id, float val) override;
    void setFeedback(float _feedback);
    void setPolarity(bool _invertPolarity);

    void setModDepth(float val);
    void setRate(float val);

    private:
    Oscillator* osc;
    float modDepth = 250;
    float offset = 88.2;
    CircBuffer circBuffer;
    bool invertPolarity;
    float feedback;
    float modFreq;

    float LFO = 0;
};