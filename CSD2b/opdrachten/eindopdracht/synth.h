#ifndef SYNTH_H
#define SYNTH_H 
#include <iostream>
#include "oscillator.h"
#include "sine.h"


class Synth
{
public:
    Synth(float midiPitch, double samplerate);
    ~Synth();

// go to next sample
void tick();

//setters and getters
double getSample();
void setMidiPitch(float pitch);


private:
    double sample = 0;
    double mtof(float pitch);
    float midiPitch;


    Oscillator *oscillator;
    Sine sine;
};

#endif
