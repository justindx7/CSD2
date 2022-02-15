#pragma once
#include "effect.h"
#include "circBuffer.h"
#include <iostream>

class Delay : public Effect
{
 public:
 Delay(float drywet, bool bypass, unsigned int samplerate, int delayMS, float feedback);
 ~Delay();
 
 //setters and getters
 void setFeedback(float _feedback);
 void setDelayTime(float ms);
 void tick() override;
 //when baseclass is better u can make this private
float process(float sample) override;

private:
float MStoSample(float ms);


//output sample
float feedback = 0;
float samplerate;

CircBuffer circBuffer;
};