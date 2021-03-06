#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "effect.h"
#include "AudioFile.h"
#include "writeToFile.h"

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
  float* buffer = nullptr; //should be dynamically allocated since there are two ways to fill the buffer
  WriteToFile* writeFile = nullptr;

  float floatCount;
  float drywet;
  float currentSample;
  float begin;
  float end;
  float k;
  int vectorSize;
  int numSamples;
  int channel;
  std::string wav;

  void fillBuffer();
  void calcAverage(float k); //sampleAverage
  void allSamples();
  void pickSample();

};
