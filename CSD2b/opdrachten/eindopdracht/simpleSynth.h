#ifndef SIMPLESYNTH_H
#define SIMPLESYNTH_H
#include <iostream>
#include "oscillator.h"
#include "synth.h"
#include "jack_module.h"



class SimpleSynth : public Synth
{
public:
    SimpleSynth(float midiPitch, Oscillator* oscillator);
    ~SimpleSynth();

    //calculate sample
    void calc() override;

private:
    Oscillator* oscillator;
};

#endif
