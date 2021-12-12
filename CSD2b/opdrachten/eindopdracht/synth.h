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

    virtual void tick() = 0;
    static double getSampleRate();
    static void setSampleRate(double newSamplerate);

protected:
    //  virtual void calculate() = 0;
    double midiToFrequency(float pitch);

private:
    float midiPitch;
    float amplitude;
    static double samplerate;
};

#endif
