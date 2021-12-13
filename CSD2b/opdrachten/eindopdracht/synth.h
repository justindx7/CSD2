#ifndef SYNTH_H
#define SYNTH_H
#include <iostream>
#include <math.h>
#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"


class Synth
{
public:
    Synth(float midiPitch);
     virtual~Synth();


    void tick();

    double getSample();

    float getMidiPitch();
    static double getSampleRate();
    static void setSampleRate(double newSamplerate);

    void setMidiPitch(float pitch);

    void setSample(double newSample);


protected:

    double midiToFrequency(float pitch);
    float midiPitch;

private:
    virtual void calculate() = 0;
    float amplitude;
    static double samplerate;

    double sample = 0;

};

#endif
