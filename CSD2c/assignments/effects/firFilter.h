#pragma once
#include <iostream>
#include "effect.h"
#include "circBuffer.h"
#include "oscillator.h"

class FirFilter : public Effect
{
public:
    FirFilter(float drywet, bool bypass, 
    unsigned int samplerate);
    ~FirFilter();
    float process(float sample) override;
    void setParameter(std::string id, float val) override;
    void tick() override;

    private:
    float lfo = 0;
    Oscillator* osc;
    float history1 = 0;
    float feedback; 
};