#ifndef NOISESYNTH_H
#define NOISESYNTH_H
#include <iostream>
#include "oscillator.h"
#include "synth.h"
#include "jack_module.h"
#include "noise.h"




class NoiseSynth : public Synth
{
public:
    NoiseSynth(float midiPitch);
    ~NoiseSynth();

private:
    void calculate() override;
    void updateFrequency(double freq) override;
    Noise noise;
};

#endif