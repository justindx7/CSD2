#include "noise.h"
#include "math.h"

Noise::Noise(float frequency, double amplitude) 
  : Oscillator(frequency, amplitude)
{
  std::cout << "Noise - constructor\n";
  srand(time(NULL));
}

Noise::~Noise() 
{
  std::cout << "Noise - destructor\n";
}

void Noise::calcNextSample()
{
  // calculate noise
  float rnd = rand() % 100;
  rnd = rnd/100;
  setSample(rnd);
}
