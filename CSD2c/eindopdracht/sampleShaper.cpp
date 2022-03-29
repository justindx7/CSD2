#include "math.h"
#include "sampleShaper.h"
#include "interpolation.h"
#include <numeric>
AudioFile<float> audioFile1;

SampleShaper::SampleShaper(float drywet,bool bypass, unsigned int samplerate, float k) :
Effect(drywet,bypass,samplerate),
floatCount(-1), currentSample(0), begin(0), end(0), k(k),
vectorSize(0), numSamples(0), channel(0)
{
  std::cout << "SampleShaper - Constructor " << std::endl;
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
  sample += 1;
  float interpolatedValue = Interpolation::scale(sample,0,2.1,0,vectorSize);
  int intS = (int) interpolatedValue;
  float y = Interpolation::linMap(interpolatedValue,intS,intS+1,v[intS],v[intS+1]);
  return y;
}

void SampleShaper::pickSample()
{
  //pick a sample by dragging a wav into terminal
  audioFile1.load("/Users/Julia/Documents/Atom/HKU/CSD2c/3.les/audio/eigenEffect/samples/OH.wav");
  audioFile1.printSummary();
  numSamples = audioFile1.getNumSamplesPerChannel();
  numSamples -= 1;
  //else the buffer exeeds how many samples the wav has
  audioFile1.setBitDepth(24);
  fillBuffer();
}

void SampleShaper::fillBuffer()
{
  //should be called in pickSample
  //fill buffer with sample
  //pick a samples
  //fill vector either with allSamples or averageSample
  calcAverage(k);
  // allSamples();
  vectorSize = v.size();
  std::cout << "SampleShaper::fillBuffer - vectorSize = " << vectorSize << std::endl;
  delete buffer;
  buffer = nullptr;
  buffer = new float[vectorSize];
  //delete and make a new buffer since when this function is called the buffer will be a different size
  begin = v.front();
  end = v.back();
  std::cout << "SampleShaper::fillBuffer - begin = " << begin << std::endl;
  std::cout << "SampleShaper::fillBuffer - end = " << end << std::endl;
  //use floats begin and end for scaling from [begin,end] to [-1,1]
  for(int i = 0; i< vectorSize; i++)
  //actually fill the buffer
  {
    float vectorIndex = v[i];
    std::cout << "SampleShaper::fillBuffer - vectorIndex = " << vectorIndex << "\n";
    float interpolatedValue = Interpolation::mapInRange(vectorIndex,begin,end,-1,1);
    // std::cout << "SampleShaper::fillBuffer - interpolatedValue = " << interpolatedValue << std::endl;
    buffer[i] = interpolatedValue;
    std::cout << "SampleShaper::fillBuffer - buffer[i] = " << buffer[i] << "\n\n";
    writeFile->write(std::to_string(buffer[i]) + "\n");
  }
  v.clear();
}

void SampleShaper::calcAverage(float k)
{
  //a vector with numbers should be called from fillBuffer
  //calcuate average value for every .x number in the vector
  //delete and then dynamically allocate a buffer + bufSize
  //might use a sigmoid as well in this function??
  //clear the vector
  std::cout << "SampleShaper::calcAverage" << std::endl;
  bool running = true;
  while(running)
  {
    for(int i = 0; i < numSamples; i++)
  //   //walks through the number of samples
    {
      currentSample = audioFile1.samples[channel][i];
      if(currentSample < floatCount +0.1 && currentSample > floatCount)
      {
        // cout << "if(currentSample < floatCount+0.1 || currentSample > floatCount) " << "if(" << currentSample <<" < "<< floatCount+0.1 << " || " << currentSample << " > " << floatCount << endl;
        std::cout << "currentSample is within range  [floatCount, floatCount-0.1]  = [" << floatCount+0.1 << ", " << floatCount << "]" << std::endl;
        std::cout << "currentSample is at number = " << currentSample << "\n\n";
        a.push_back(currentSample);
      }
    }
    if(floatCount <= 1)
    {
      float k = 5;
      float normalizeFactor = 1.0f / atan(k);
      float sum  = accumulate(a.begin(),a.end(),0.0f);
      float average = sum/a.size();
      std::cout << "SampleShaper::calcAverage - a.size(), sum, average = " << a.size() << ", " << sum << ", " << average << "\n\n";
      if(average < 1 && average> -1){
        v.push_back(normalizeFactor * atan(k * average));
      }
      a.clear();
      floatCount += 0.1;
    }
    else {running = false;}
  }
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
    currentSample = audioFile1.samples[channel][i];
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

// E^iomega = cos(omega)+ isin(omega)
