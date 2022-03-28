#include "math.h"
#include "sampleShaper.h"
#include "interpolation.h"
#include <numeric>
AudioFile<float> audioFile1;
#include "sine.h"

SampleShaper::SampleShaper(float drywet,bool bypass, unsigned int samplerate, float k) :
Effect(drywet,bypass,samplerate),
currentSample(0), floatCount(-1), begin(0), end(0), k(k),
vectorSize(0), numSamples(0), channel(0)
{
  // pickSample();
}

SampleShaper::~SampleShaper()
{
  delete buffer;
  buffer = nullptr;
}



float SampleShaper::applyEffect(float sample)
{
  sample += 1;
  float interpolatedValue = Interpolation::scale(sample,0,2.1,0,vectorSize);
  int intS = (int) interpolatedValue;
  float y = Interpolation::linMap(interpolatedValue,intS,intS+1,v[intS],v[intS+1]);
  return y;
}

void SampleShaper::pickSample()
{
  //pick a sample by dragging a wav into terminal
  audioFile1.load(wav);
  std::cout << "SampleShaper::pickSample - wav " << wav << std::endl;
  audioFile1.printSummary();
  numSamples = audioFile1.getNumSamplesPerChannel();
  numSamples -= 1;
  //else the buffer exeeds how many samples the wav has
  fillBuffer();
  std::cout << "done running pickSample" << std::endl;
}

void SampleShaper::fillBuffer()
{
  calcAverage();
  vectorSize = v.size();
  delete buffer;
  buffer = nullptr;
  buffer = new float[vectorSize];
  //delete and make a new buffer since when this function is called the buffer will likely be a different size
  begin = v.front();
  end = v.back();
  //use floats begin and end for scaling from [begin,end] to [-1,1]
  for(int i = 0; i< vectorSize; i++)
  //actually fill the buffer
  {
    float vectorIndex = v[i];
    float interpolatedValue = Interpolation::scale(vectorIndex,begin,end,-1,1);
    buffer[i] = interpolatedValue;
  }
  v.clear();
  std::cout << "done running fillBuffer" << std::endl;
  //empty the vector for possible later use
}

void SampleShaper::calcAverage()
{
  bool running = true;
  while(running)
  {
    for(int i = 0; i < numSamples; i++)
  //   //walks through the number of samples
    {
      currentSample = audioFile1.samples[channel][i];
      if(currentSample < floatCount +0.1 && currentSample > floatCount) {a.push_back(currentSample);}
      //stores every .x number in  a vector
    }
    if(floatCount <= 1)
    {
      float normalizeFactor = 1.0f / atan(k);
      float sum  = accumulate(a.begin(),a.end(),0.0f);
      float average = sum/a.size();
      if(average < 1 && average> -1){
        v.push_back(normalizeFactor * atan(k * average));
        //calculate average per .x number and add it into anothe vector with sigmoid
      }
      a.clear();
      //empty vector
      floatCount += 0.1;
    //increase floatcount so every next .x value gets stored into a vector
    }
    else {running = false;}
    std::cout << "done running calcAverage" << std::endl;
  }
}

void SampleShaper::setParameter(std::string id, float val)
{
  if( id == "pickSample")
  {
    k = val;
    std::cin >> wav;
    //drag a sample into the terminal and press enter
    pickSample();
  }
}

// E^iomega = cos(omega)+ isin(omega)