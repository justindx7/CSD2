#include "waveShaper.h"
#include "wavetableGenerator.h"

#define bufferSize 4069
float buffer[bufferSize];

WaveShaper::WaveShaper(float drywet, bool bypass, unsigned int samplerate)
: Effect(drywet, bypass, samplerate)
{
    WavetableGenerator::generateSCurve(buffer, bufferSize, 2.0F);
}

WaveShaper::~WaveShaper()
{
}

float WaveShaper::mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh )
{
    float output;
    output = yLow + (value - xLow) * ((yHigh - yLow) / (xHigh - xLow));
    return output;
}

float WaveShaper::linMap(float value, int low, int high)
{
    float output;
    output = mapInRange(value, 0,0,low,high);
    return output;
}


float WaveShaper::process(float sample)
{
    float index = mapInRange(sample, -1, 1, 0, bufferSize -1) + 0.5;
    int i = (int)index;
    float indexDecimal = index - (float)i;
    return linMap(indexDecimal, buffer[i], buffer[i + 1]);
}

void WaveShaper::setParameter(std::string id, float val){}
void WaveShaper::tick(){}