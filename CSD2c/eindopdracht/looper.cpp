#include "sine.h"
#include "saw.h"
#include "triangle.h"
#include "looper.h"
AudioFile<float> audioFile;

//to use this effect setParameter should be called first, to load a wav file
Looper::Looper(float drywet, bool bypass, unsigned int samplerate) :
Effect(drywet,bypass,samplerate),
currentSample(0),numSamples(0) ,modFreq(1)
{
  std::cout << "looper" << std::endl;
}
//LFO in
//select waveform

Looper::~Looper()
{
  delete osc;
  osc = nullptr;
  delete buffer;
  buffer = nullptr;
}

float Looper::applyEffect(float sample)
{
  float sine = osc->getSample();
  osc->genNextSample();
  sine += 1;
  float interpolatedValue = Interpolation::scale(sine,0,2.1,0,numSamples);
  int intS = (int) interpolatedValue;
  float y = Interpolation::linMap(interpolatedValue,intS,intS+1,buffer[intS],buffer[intS+1]);
  //interpolate between sine value and place in buffer to walk though wav
  return y;
}

void Looper::setParameter(std::string id, float val)
{
  if( id == "pickSample")
  {
     val;
    std::cin >> wav;
    fillBuffer();
  }
}

void Looper::fillBuffer()
{
  audioFile.load(wav);
  audioFile.printSummary();
  numSamples = audioFile.getNumSamplesPerChannel();
  numSamples -= 1;
  //else the buffer exeeds how many samples the wav has
  delete buffer;
  buffer = nullptr;
  buffer = new float[numSamples];
  int channel = 0;
  for(int i = 0; i < numSamples; i++)
  {
    currentSample = audioFile.samples[channel][i];
    buffer[i] = currentSample;
    //fill the buffer with audio file
  }
}