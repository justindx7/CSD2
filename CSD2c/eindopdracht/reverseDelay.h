#pragma once
#include "effect.h"
#include "circBuffer.h"
#include <iostream>
#include <queue>
#include <vector>

class ReverseDelay : public Effect
{
 public:
 ReverseDelay(float drywet, bool bypass, unsigned int samplerate);
 ~ReverseDelay();
 
private:
void setParameter(std::string id, float val) override;
float applyEffect(float sample) override;
float MStoSample(float ms);
 //setters and getters
void setDelayTime(float ms);
std::vector<float> buffer;
std::vector<float> reverseBuffer;
//output sample
float samplerate;

CircBuffer circBuffer;
};