#pragma once
#include <iostream>
#include "effect.h"
#include "oscillator.h"


class Tremolo : public Effect
{
public:
  Tremolo(float drywet, bool bypass, unsigned int samplerate, float modFreq);
  ~Tremolo();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;

private:
  Oscillator* osc = nullptr;
  void setModFreq(float val);
  float modFreq;
};
