#ifndef OSCILLATOR_H
#define OSCILLATOR_H 
#include <iostream>

class Oscillator 
{

public:
    Oscillator(float frequency, double amplitude);
    // if a class has virtual functions its destructor should also be virtual
    virtual ~Oscillator();

    void setFrequency(float frequency);
    float getFrequency();


    void setSample(float newSample);

    float getSample();

    float getAmplitude();
    
    void tick();


protected:
    double getSampleRate();
    double phase = 0;
    virtual void calcNextSample() = 0;
    
private:
    float frequency;
    double amplitude;
    float sample = 0;
};

#endif