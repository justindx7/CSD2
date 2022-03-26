#pragma once
#include <iostream>
#include "effect.h"
#include "AudioFile.h"
#include "oscillator.h"
#include "interpolation.h"
#include "writeToFile.h"

class Looper : public Effect
{
public:
  Looper(float drywet, bool bypass, unsigned int samplerate);
  ~Looper();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;
  float scale(float y, float x1From, float x2From, float x1To, float x2To);
  float interpolation(float x, float x1, float x2, float y1, float y2);

private:
  float* buffer = nullptr;
  Oscillator* osc = nullptr;
  WriteToFile* writeFile = nullptr;

  float numSamples;
  float currentSample;

  void fillBuffer();

};
