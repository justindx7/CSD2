#include "sine.h"
#include "tremolo.h"
#include "saw.h"
#include "square.h"


Tremolo::Tremolo(float drywet, bool bypass, unsigned int samplerate, float freq, WaveformType waveformType) 
 : Effect(drywet, bypass, samplerate)
{
switch(waveformType){
  case WaveformType::SINE:
  {
  osc = new Sine(freq, samplerate);
  break; 
  }
  case WaveformType::SAW:
  {
  osc = new Saw(freq, samplerate);
  break; 
  }
  case WaveformType::SQUARE:
  {
  osc = new Square(freq, samplerate);
  break; 
  }
}
}

Tremolo::~Tremolo()
{
    delete osc;
    osc = nullptr;
}

void Tremolo::setModFreq(float freq)
{
  osc->setFrequency(freq);
}

float Tremolo::process(float sample)
{
  modSignal = (osc->genNextSample() + 1.0f) * 0.5f;
  //drywet signal
  modSignal *= drywet;
  modSignal += 1.0 - drywet;
 return  sample * modSignal;
}