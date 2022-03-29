#include "reverseDelay.h"
#include "circBuffer.h"
#include "interpolation.h"


ReverseDelay::ReverseDelay(float drywet, bool bypass, unsigned int samplerate)
    : Effect(drywet, bypass, samplerate), samplerate(samplerate)
{
}

ReverseDelay::~ReverseDelay()
{
}

// does effect
float ReverseDelay::applyEffect(float sample)
{
    buffer.push_back(sample);
    if (buffer.size() == (samplerate * 4)-1)
    {
        std::swap(buffer, reverseBuffer);
    }
    if (reverseBuffer.empty())
    {
        modSample = sample;
    }
    else
    {
        //TODO interpolate singal so no loud click at the end
        float result = reverseBuffer.back();
        reverseBuffer.pop_back();
        modSample = result;
    }
    return modSample;
}

// convert miliseconds to samplerate
float ReverseDelay::MStoSample(float ms)
{
    std::cout << 44100 * (ms / 1000) << "\n";
    return samplerate * (ms / 1000);
}

void ReverseDelay::setDelayTime(float ms)
{
    // TODO use lineair interpolation to not have clicks while changing time
    // this doesn't click when time is changed right now weird
    circBuffer.setDistanceRW(MStoSample(ms));
}
// get a name and an value and check input then change value
void ReverseDelay::setParameter(std::string id, float val)
{
    // TODO add size changer or make the size bigger and smaller using the time.
    if (id == "delayTime")
    {
        if (val <= 1000)
        {
            setDelayTime(val);
        }
        else
        {
            std::cout << "delay time cant be higher than size" << std::endl;
        }
    }
}