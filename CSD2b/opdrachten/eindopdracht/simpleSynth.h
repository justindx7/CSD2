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

    // go to next sample
    void tick() override;

    //setters and getters
    double getSample();
    void setMidiPitch(float pitch);

private:
    Oscillator* oscillator;
};

#endif
