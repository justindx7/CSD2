#ifndef OSCILLATOR_H
#define OSCILLATOR_H 
#include <iostream>
#include "synth.h"



class Oscillator 
{

public:
    Oscillator(float frequency);
    // if a class has virtual functions its destructor should also be virtual
    virtual ~Oscillator();

    void setFrequency(float frequency);
    float getFrequency();

    void setSample(float newSamplerate);

    float getSample();
    void tick();

    virtual void calculate() = 0;

protected:
    double getSampleRate();

private:
    float frequency;
    float sample = 0;
};

#endif