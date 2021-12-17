#ifndef SQUARESYNTH_H
#define SQUARESYNTH_H
#include <iostream>
#include "oscillator.h"
#include "synth.h"
#include "jack_module.h"
#include "square.h"
#include <vector>





class SquareSynth : public Synth
{
public:
    SquareSynth(float midiPitch);
    ~SquareSynth();

private:
    void calculate() override;
    void updateFrequency(double freq) override;

    std::vector<Oscillator*> createOscillators(float frequency, double amplitude);

    std::vector<Oscillator*> oscillators;

    double detune[2] = {-5,5};
};

#endif