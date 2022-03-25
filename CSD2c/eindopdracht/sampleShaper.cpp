#include "math.h"
#include "sampleShaper.h"
#include "interpolation.h"
#include <numeric>
AudioFile<float> audioFile;

SampleShaper::SampleShaper(float drywet,bool bypass, unsigned int samplerate, float k) :
Effect(drywet,bypass,samplerate),
normalizeFactor(1.0f), currentSample(0), floatCount(-1), begin(0), end(0), k(k),
vectorSize(0), numSamples(0), channel(0)
{
  writeFile = new WriteToFile("output.csv",true);
  pickSample();
}

SampleShaper::~SampleShaper()
{
  delete buffer;
  delete writeFile;
  buffer = nullptr;
  writeFile = nullptr;
}



float SampleShaper::applyEffect(float sample)
{
  // sample += 1;
  // float interpolatedValue = Interpolation::mapInRange(sample,0,2,0,vectorSize);
  float interpolatedValue = Interpolation::mapInRange(sample,-1,1,0,vectorSize);
  int intS = (int) interpolatedValue;
  float y = Interpolation::linMap(interpolatedValue,v[intS],v[intS+1]);
  return y;
}

void SampleShaper::pickSample()
{
  //pick a sample by dragging a wav into terminal
  audioFile.load("/Users/Julia/Documents/Atom/HKU/CSD2c/3.les/audio/eigenEffect/samples/SUB.wav");
  audioFile.printSummary();
  numSamples = audioFile.getNumSamplesPerChannel();
  numSamples -= 1;
  //else the buffer exeeds how many samples the wav has
  audioFile.setBitDepth(24);
  fillBuffer();
}

void SampleShaper::fillBuffer() //add k factor in the forloop in here
{
  normalizeFactor /= atan(k);
  calcAverage();
  // allSamples();
  vectorSize = v.size();
  delete buffer;
  buffer = nullptr;
  buffer = new float[vectorSize];
  //delete and make a new buffer since when this function is called the buffer will be a different size
  begin = v.front();
  end = v.back();
  //use floats begin and end for scaling from [begin,end] to [-1,1]
  for(int i = 0; i< vectorSize; i++)
  //actually fill the buffer
  {
    // float vectorIndex = normalizeFactor * atan(k * v[i]);
    float vectorIndex = v[i];
    float interpolatedValue = Interpolation::mapInRange(vectorIndex,begin,end,-1,1);
    buffer[i] = interpolatedValue;
    std::cout << "SampleShaper::fillBuffer - buffer[i] = " << buffer[i] << std::endl;
    std::cout << "SampleShaper::fillBuffer - interpolatedValue = " << interpolatedValue << std::endl;
    writeFile->write(std::to_string(buffer[i]) + "\n");
  }
  v.clear();
}

void SampleShaper::calcAverage()
{
  bool running = true;
  while(running)
  {
    for(int i = 0; i < numSamples; i++)
  //   //walks through the number of samples
    {
      currentSample = audioFile.samples[channel][i];
      if(currentSample < floatCount +0.1 && currentSample > floatCount) {a.push_back(currentSample);}
    }
    if(floatCount <= 1)
    {
      // normalizeFactor /= atan(k);
      float sum  = accumulate(a.begin(),a.end(),0.0f);
      float average = sum/a.size();
      std::cout << "SampleShaper::calcAverage - a.size(), sum, average = " << a.size() << ", " << sum << ", " << average << "\n\n";
      if(average < 1 && average> -1){
        // v.push_back(normalizeFactor * atan(k * average));
        v.push_back(average);
      }
      a.clear();
      floatCount += 0.1;
    }
    else {running = false;}
  }
}

void SampleShaper::allSamples()
{
  for(int i = 0; i < numSamples; i++)
  // fill vector with samples from wav
  {
    currentSample = audioFile.samples[channel][i];
    // stores the current sample from the wav in currentSample
    if(currentSample > 0.0009 || currentSample < -0.0009) {v.push_back(currentSample);}
    // removes the x...9 numbers before storing the samples in the vector, since a having a lot of x.00 numbers make for a very boring waveshaper
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

// E^iomega = cos(omega)+ isin(omega)
