#include "interpolation.h"

Interpolation::Interpolation() {}

Interpolation::~Interpolation() {}

// static to make them available in all classes without declaring the class

float Interpolation::NNMap(float value, float low, float high)
{

    return (value > 0.5) ? low : high;
}

float Interpolation::mapInRange(float value, float xLow, float xHigh, float yLow, float yHigh)
{
    float output;
    output = yLow + ((yHigh-yLow)/(xHigh-xLow)) * (value - xLow);
    return output;
}
float Interpolation::linMap(float value, float low, float high)
{
    float output;
    output = mapInRange(value, 0,1,low,high);
    return output;
}