#include "interpolation.h"

Interpolation::Interpolation() {}

Interpolation::~Interpolation() {}

// static to make them available in all classes without declaring the class

float Interpolation::NNMap(float value, int low, int high)
{

    return (value > 0.5) ? low : high;
}

float Interpolation::mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh)
{
    float output;
    output = yLow + (value - xLow) * ((yHigh - yLow) / (xHigh - xLow));
    return output;
}
float Interpolation::linMap(float value, int low, int high)
{
    float output;
    output = mapInRange(value, 0, 0, low, high);
    return output;
}