#include "delay.h"
#include "circBuffer.h"

Delay::Delay(float drywet, bool bypass, unsigned int samplerate, int delayMS , float feedback)
:Effect(drywet, bypass, samplerate), feedback(feedback), samplerate(samplerate)
{
    circBuffer.resetSize(samplerate);
    circBuffer.setDistanceRW(MStoSample(delayMS));
}

Delay::~Delay()
{
}

float Delay::process(float sample)
{
  circBuffer.write(sample + (output * feedback));
  output = circBuffer.read();
  output *= drywet;
  output += sample + 1.0 - drywet;
 return output;
}

void Delay::tick()
{
    circBuffer.tick();
}

void Delay::setFeedback(float _feedback)
{
    if(_feedback > 0 && _feedback < 1){
        feedback = _feedback;
    }
}

float Delay::MStoSample(float ms)
{
std::cout << 44100 * (ms / 1000) << "\n";
return samplerate * (ms / 1000);
}

void Delay::setDelayTime(float ms)
{
    circBuffer.setDistanceRW(MStoSample(ms));
}
