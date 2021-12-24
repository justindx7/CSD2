#ifndef SIMPLESYNTH_H
#define SIMPLESYNTH_H
#include <iostream>
#include "oscillator.h"
#include "synth.h"
#include "jack_module.h"
#include "triangle.h"



class SimpleSynth : public Synth
{
public:
    SimpleSynth(float midiPitch);
    ~SimpleSynth();

private:
    void calculate() override;
    void updateFrequency(double freq) override;
    Triangle triangle;
};

#endif