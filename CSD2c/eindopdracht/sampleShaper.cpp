#include "pickSample.h"
AudioFile<float> audioFile;
#include <numeric>

SampleShaper::SampleShaper(float drywet,bool bypass) :
effect(drywet,bypass), floatCount(0), vectorSize(0), bufSize(0)
{
  cout << "SampleShaper - Constructor " << endl;
}

SampleShaper::~SampleShaper()
{}
  
