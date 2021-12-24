#include "triangle.h"
#include "math.h"

Triangle::Triangle(float frequency, double amplitude) 
  : Oscillator(frequency, amplitude)
{
  std::cout << "Triangle - constructor\n";
}

Triangle::~Triangle() 
{
  std::cout << "Triangle - destructor\n";
}

void Triangle::calcNextSample()
{
  // calculate triangle wave
  setSample((2/M_PI) * asin(sin(M_PI * (phase *2))));
}
