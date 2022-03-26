#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "effect.h"
#include "AudioFile.h"
#include "writeToFile.h"
#include "oscillator.h"

class SampleShaper : public Effect
{
public:
  SampleShaper(float drywet,bool bypass, unsigned int samplerate);
  ~SampleShaper();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;
  void sine();

private:
  std::vector<float> v;
  std::vector<float> a;
  float* buffer = nullptr; //should be dynamically allocated since there are two ways to fill the buffer
  WriteToFile* writeFile = nullptr;
  Oscillator* osc;

  float currentSample;
  float floatCount;
  float drywet;
  float begin;
  float end;
  int vectorSize;
  int numSamples;
  int channel;
  std::string wav;

  void fillBuffer();
  void calcAverage(); //sampleAverage
  void allSamples();
  void pickSample();

};
