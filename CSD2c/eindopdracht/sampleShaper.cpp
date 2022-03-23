#include "sampleShaper.h"
AudioFile<float> audioFile;
#include <numeric>
#include "math.h"

SampleShaper::SampleShaper(float drywet,bool bypass, unsigned int samplerate) :
Effect(drywet,bypass,samplerate),
floatCount(-1), vectorSize(0), bufSize(0), numSamples(0)
{
  std::cout << "SampleShaper - Constructor " << std::endl;
}

SampleShaper::~SampleShaper()
{
  delete buffer;
  delete interpolate;
  buffer = nullptr;
  interpolate = nullptr;
}



float SampleShaper::applyEffect(float sample)
{
  //should use interpolation over here 
  return 0;
}

void SampleShaper::pickSample()
{
  //pick a sample by dragging a wav into terminal
}

void SampleShaper::fillBuffer()
{
  //should be called in pickSample
  //fill buffer with sample
  //pick a samples
  //fill buffer either with allSamples or averageSample
  //actually fill the buffer
}

void SampleShaper::calcAverage()
{
  //a vector with numbers should be called from fillBuffer
  //calcuate average value for every .x number in the vector
  //delete and then dynamically allocate a buffer + bufSize
  //might use a sigmoid as well in this function??
  //clear the vector
}

void SampleShaper::allSamples()
{
  //use almost all the samples (exept for the samples that are very close to 0 since there are a lot of those in most wavs)
  //fill all the samples exept the one named above in a vector
  //sort the vector from low to high
  //use the .size() function to retrieve the size the buffer should be
  //delete and then dynamically allocate buffer
}

void SampleShaper::setParameter(std::string id, float val)
{}
