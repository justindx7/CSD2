#include "triangle.h"
#include "math.h"


Triangle::Triangle() : Triangle(0, 0)
{}

Triangle::Triangle(float frequency, float samplerate) :
  Oscillator(frequency, samplerate) {}

Triangle::~Triangle() {}

void Triangle::calcNextSample()
{
  sample = (2/M_PI) * asin(sin(M_PI * (phase *2)));
  // TODO - move to base class
  sample *= amplitude;
}
