#ifndef OSCILLATOR_H
#define OSCILLATOR_H 
#include <iostream>


class Oscillator 
{

public:
    Oscillator(float frequency, double samplerate);
    // if a class has virtual functions its destructor should also be virtual
    virtual ~Oscillator();

    void setFrequency(float frequency);
    float getFrequency();

    void setSampleRate(double newSamplerate);
    double getSampleRate();

    void setSample(float newSamplerate);

    float getSample();
    void tick();

    virtual void calculate() = 0;

private:
    float frequency;
    double samplerate;
    float sample = 0;
};

#endif