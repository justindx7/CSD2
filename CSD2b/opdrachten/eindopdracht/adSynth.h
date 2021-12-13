#ifndef ADSYNTH_H
#define ADSYNTH_H
#include <iostream>
#include "oscillator.h"
#include "synth.h"
#include "jack_module.h"
#include "square.h"
#include <vector>





class AdSynth : public Synth
{
public:
    AdSynth(float midiPitch);
    ~AdSynth();

private:
    void calculate() override;
    static std::vector<Oscillator*> createOscillators(float frequency, double amplitude);

    std::vector<Oscillator*> oscillators;
};

#endif