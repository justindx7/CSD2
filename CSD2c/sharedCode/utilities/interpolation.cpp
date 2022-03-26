#include "interpolation.h"

Interpolation::Interpolation() {}

Interpolation::~Interpolation() {}

// static to make them available in all classes without declaring the class

float Interpolation::NNMap(float value, float low, float high)
{

    return (value > 0.5) ? low : high;
}

float Interpolation::scale(float y, float x1From, float x2From, float x1To, float x2To)
{
  float delta = x2From - x1From;
  float yScaled = y/delta;
  std::cout << yScaled << std::endl;
  float newBufSize = x2To - x1To;
  float scale = (yScaled * newBufSize) + x1To;
  return scale;
}

float Interpolation::linMap(float x, float x1, float x2, float y1, float y2)
{
  float y = y1 + (y2-y1) * ((x-x1) / (x2-x1));
  return y;
}
