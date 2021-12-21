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
    void updateFrequency(double freq) override;

    float freqRatios[11] = {0.56, 1.56, 0.92, 2.62, 1.19, 1.7, 2.0, 2.74, 3.0, 3.7, 4.07};

    std::vector<Oscillator*> createOscillators(float frequency, double amplitude);
    std::vector<Oscillator*> oscillators;
};

#endif