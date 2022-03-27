#pragma once
#include <iostream>
#include "effect.h"
#include "AudioFile.h"
#include "oscillator.h"
#include "interpolation.h"

class Looper : public Effect
{
public:
  Looper(float drywet, bool bypass, unsigned int samplerate);
  ~Looper();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;

private:
  float* buffer = nullptr;
  Oscillator* osc = nullptr;

  float numSamples;
  float currentSample;
  float modFreq;
  std::string wav;

  void fillBuffer();
};
