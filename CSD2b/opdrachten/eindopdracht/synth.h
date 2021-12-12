#ifndef SYNTH_H
#define SYNTH_H
#include <iostream>
#include <math.h>
#include <vector>
#include "jack_module.h"
#include "oscillator.h"

class Synth
{
public:
    Synth(float midiPitch);
    virtual ~Synth();

    virtual void calc() = 0;

    void tick();

    float getSample();
    float getMidiPitch();
    static double getSampleRate();
    static void setSampleRate(double newSamplerate);

    void setSample(float newSample);


protected:
    //  virtual void calculate() = 0;
    double midiToFrequency(float pitch);
    float midiPitch;

private:
    float amplitude;
    static double samplerate;

    float sample = 0;

};

#endif
