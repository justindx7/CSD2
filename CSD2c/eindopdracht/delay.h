#pragma once
#include "effect.h"
#include "circBuffer.h"
#include <iostream>

class Delay : public Effect
{
 public:
 Delay(float drywet, bool bypass, unsigned int samplerate, int delayMS, float feedback);
 ~Delay();
 
private:
void setParameter(std::string id, float val) override;
float applyEffect(float sample) override;
float MStoSample(float ms);
 //setters and getters
void setFeedback(float _feedback);
void setDelayTime(float ms);


//output sample
float feedback = 0;
float samplerate;

CircBuffer circBuffer;
};