#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "effect.h"
#include "AudioFile.h"

class SampleShaper : public Effect
{
public:
  SampleShaper(float drywet,bool bypass, unsigned int samplerate, float k);
  ~SampleShaper();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;

private:
  std::vector<float> v;
  std::vector<float> a;
  float* buffer = nullptr;

  float currentSample;
  float floatCount;
  float begin;
  float end;
  float k;
  int vectorSize;
  int numSamples;
  int channel;
  std::string wav;

  void fillBuffer();
  void calcAverage();
  void pickSample();

};