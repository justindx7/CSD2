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


float process(float sample) override;
void tick();

float MStoSample(float ms);


//output sample
float output = 0;
float feedback = 0;
float samplerate;

CircBuffer circBuffer;

};