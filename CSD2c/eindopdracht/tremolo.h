#pragma once
#include <iostream>
#include "effect.h"
#include "oscillator.h"
using namespace std;


class Tremolo : public Effect
{
public:
  Tremolo(float drywet, bool bypass, unsigned int samplerate);
  ~Tremolo();

  void setModFreq(float val);
  float applyEffect(float sample) override;
  void setParameter(string id, float val) override;

private:
  Oscillator* osc = nullptr;
};
