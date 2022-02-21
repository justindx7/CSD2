#pragma once
#include <iostream>
#include "oscillator.h"
#include "effect.h"


class Tremolo : public Effect
{
public:
  enum WaveformType {
    SINE = 0, // ensure enum starts at 0
    SAW,
    SQUARE,
    SIZE // 3
  };
    Tremolo(float drywet, bool bypass, 
    unsigned int samplerate, float freq, WaveformType waveformType = WaveformType::SINE);
    ~Tremolo();


    //setters and getters
    void setModFreq(float freq);
    float process(float sample) override;
    void setParameter(std::string id, float val) override;
    void tick() override;

    private:
    Oscillator* osc;
    float modSignal;
};