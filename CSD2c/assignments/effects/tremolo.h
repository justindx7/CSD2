#pragma once
#include <iostream>
#include "oscillator.h"
#include "effect.h"


class Tremolo : public Effect
{
public:
    Tremolo(float freq, float drywet, bool bypass, unsigned int samplerate);
    ~Tremolo();


    //setters and getters
    void setModFreq(float freq);
    
    private:
    float process(float sample) override;
    Oscillator* osc;
};