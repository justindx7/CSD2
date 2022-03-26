#include "sine.h"
#include "looper.h"
AudioFile<float> audioFile;

Looper::Looper(float drywet, bool bypass, unsigned int samplerate) :
Effect(drywet,bypass,samplerate),
currentSample(0)
{
  std::cout << "Looper - Constructor " << std::endl;
  osc = new Sine(1,samplerate);
  writeFile = new WriteToFile("output.csv",true);
  fillBuffer();
}

Looper::~Looper()
{
  delete osc;
  osc = nullptr;
  delete buffer;
  buffer = nullptr;
  delete writeFile;
  writeFile = nullptr;
}

float Looper::applyEffect(float sample)
{
  float sine = osc->getSample();
  osc->genNextSample();
  sine += 1;
  float interpolatedValue = Interpolation::scale(sine,0,2.1,0,numSamples);
  int intS = (int) interpolatedValue;
  float y = Interpolation::linMap(interpolatedValue,intS,intS+1,buffer[intS],buffer[intS+1]);
  writeFile->write(std::to_string(y) + "\n");
  return y;
}

void Looper::setParameter(std::string id, float val)
{

}

void Looper::fillBuffer()
{
  audioFile.load("/Users/Julia/Documents/Atom/HKU/CSD2c/3.les/audio/eigenEffect/samples/OH.wav");
  audioFile.printSummary();
  numSamples = audioFile.getNumSamplesPerChannel();
  numSamples -= 1;
  std::cout << "Looper::fillBuffer - numSamples = " << numSamples << std::fixed << std::endl;
  delete buffer;
  buffer = nullptr;
  buffer = new float[numSamples];
  int channel = 0;
  //else the buffer exeeds how many samples the wav has
  for(int i = 0; i < numSamples; i++)
  {
    currentSample = audioFile.samples[channel][i];
    // std::cout << "Looper::fillBuffer - currentSample = " << currentSample << std::endl;

    buffer[i] = currentSample;
  }
  // applyEffect(0);
}

float Looper::scale(float y, float x1From, float x2From, float x1To, float x2To)
{
  float delta = x2From - x1From;
  float yScaled = y/delta;
  std::cout << yScaled << std::endl;
  float newBufSize = x2To - x1To;
  float scale = (yScaled * newBufSize) + x1To;
  return scale;
}

float Looper::interpolation(float x, float x1, float x2, float y1, float y2)
{
  float y = y1 + (y2-y1) * ((x-x1) / (x2-x1));
  // interpolation(scaledSample,i,i+1,buffer[i],buffer[i+1])
  // std::cout << "Waveshaper::interpolation - x = " << x << std::endl;
  // std::cout << "Waveshaper::interpolation - x1 = " <<x1 << std::endl;
  // std::cout << "Waveshaper::interpolation - x2 = " << x2 << std::endl;
  // std::cout << "Waveshaper::interpolation - y1 = " << y1 << std::endl;
  // std::cout << "Waveshaper::interpolation - y2 = " << y2 << std::endl;
  // std::cout << "Waveshaper::interpolation - y = " << y << std::endl;
  return y;
}
