#include "sampleShaper.h"
AudioFile<float> audioFile;
#include <numeric>
#include "math.h"

SampleShaper::SampleShaper(float drywet,bool bypass, unsigned int samplerate) :
Effect(drywet,bypass,samplerate),
floatCount(-1), currentSample(0), vectorSize(0), bufSize(0), numSamples(0), channel(0)
{
  std::cout << "SampleShaper - Constructor " << std::endl;
  writeFile = new WriteToFile("output.csv",true);
}

SampleShaper::~SampleShaper()
{
  delete buffer;
  delete interpolate;
  delete writeFile;
  buffer = nullptr;
  interpolate = nullptr;
  writeFile = nullptr;
}



float SampleShaper::applyEffect(float sample)
{
  //should use interpolation over here
  return 0;
}

void SampleShaper::pickSample()
{
  //pick a sample by dragging a wav into terminal
  audioFile.load("/Users/Julia/Documents/Atom/HKU/CSD2c/3.les/audio/eigenEffect/samples/OH.wav");
  audioFile.printSummary();
  numSamples = audioFile.getNumSamplesPerChannel();
  numSamples -= 1;
  //else the buffer exeeds how many samples the wav has
  audioFile.setBitDepth(24);
  fillBuffer();
}

void SampleShaper::fillBuffer()
{
  //should be called in pickSample
  //fill buffer with sample
  //pick a samples
  //fill vector either with allSamples or averageSample
  allSamples();
  vectorSize = v.size();
  delete buffer;
  buffer = nullptr;
  buffer = new float[vectorSize];
  //delete and make a new buffer since when this function is called the buffer will be a different size
  for(int i = 0; i< vectorSize; i++)
  //actually fill the buffer
  {
    // float s = scale(v[i],begin,end,-1,1);
    buffer[i] = v[i];
    // float s  = scale(buffer[i],begin + 1,end + 1,0, 2) -1;
    // cout << s << "\n\n\n";
    writeFile->write(std::to_string(buffer[i]) + "\n");
  }
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
  for(int i = 0; i < numSamples; i++)
  // fill vector with samples from wav
  {
    currentSample = audioFile.samples[channel][i];
    // stores the current sample from the wav in currentSample
    if(currentSample > 0.0009 || currentSample < -0.0009)
    // removes the x...9 numbers before storing the samples in the vector, since a having a lot of x.00 numbers make for a very boring waveshaper
    {
      // std::cout << "sampleAverage::allSamples - currentSample =" << currentSample <<"\n ";
      v.push_back(currentSample);
      // writeFile->write(std::to_string(currentSample) + "\n");
    }
  }
  sort(v.begin(), v.end());
}

void SampleShaper::setParameter(std::string id, float val)
{
  if( id == "pickSample")
  {
    // std::cin >> wav;
    pickSample();
  }
}
