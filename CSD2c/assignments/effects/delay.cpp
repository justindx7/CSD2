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
  circBuffer.write(sample + (modSignal * feedback));
  modSignal = circBuffer.read();
  modSignal *= getDrywet();
  modSignal += sample + 1.0 - getDrywet();
 return modSignal;
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
    //TODO use lineair interpolation to not have clicks while changing time
    circBuffer.setDistanceRW(MStoSample(ms));
}
// get a name and an value and check input then change value
void Delay::setParameter(std::string id, float val)
{
    if(id == "delayTime"){
        if(val <= 1000){
        setDelayTime(val);
        }
        else{
            std::cout << "delay time cant be higher than size" << std::endl;
        }
    }
    if(id == "feedback"){
        if(val < 1.0F){
        setFeedback(val);
        std::cout << "feedback: " << val << std::endl;
        }
        else{
            std::cout << "feedback cant be higher than 0.9" << std::endl;
        }
    }
}