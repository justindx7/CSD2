#include "square.h"
#include "math.h"


Square::Square(float frequency, double amplitude) 
  : Oscillator(frequency, amplitude)
{
  std::cout << "Square - constructor\n";
}

Square::~Square() 
{
  std::cout << "Square - destructor\n";
}

void Square::calcNextSample() {
  // calculating square
  if(phase < 0.5) {
    setSample(1.0);
  } else {
    setSample(-1.0);
  }
}

