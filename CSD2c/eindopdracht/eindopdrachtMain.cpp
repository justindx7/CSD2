#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h> // sleep
#include "jack_module.h"
#include "effect.h"
#include "chorus.h"
#include "analyzer.h"
#include "reverseDelay.h"
#include <cmath>
#include "delay.h"

#define WRITE_NUM_SAMPLES 44100
// boolean is used to keep program running / turn it off
bool running = true;

// with the marcs jack abstaraction module we dont need to know Jacks buffer size
constexpr size_t chunksize = 2048;

float samplerate = 44100; // default

float amplitude = 0.5;

// create a JackModule instance
JackModule jack;

std::vector<Effect *> effects{};

Analyzer analyzer(samplerate);

bool peaked = false;
int effectCounter = 0;

void changeEffects(int counter, float buf)
{
  double feedbackAmount;
  // scale counter to feedback amount
  feedbackAmount = (0.4 - 0.9) * (effectCounter) / (samplerate * 6) + 0.9;

  // round feedbackAmount to 3 decimals
  feedbackAmount = round(feedbackAmount * 1000.0) / 1000.0;

  if (analyzer.getPeak())
  {
    //set delay feedback high
    peaked = true;
  }
  // if peaked set the effect settings and when the feedback is <0.41 reset the counter and peaked = false
  if (peaked)
  {
    effectCounter++;
    // 0.4  // /2.25 //117600
    effects[0]->setParameter("feedback", feedbackAmount);
    effects[1]->setParameter("feedback", feedbackAmount);

    effects[0]->setParameter("modDepth", 600);
    effects[1]->setParameter("modDepth", 600);

    effects[3]->setParameter("feedback", 0.9);
    effects[3]->setParameter("DelayTime", (1 - feedbackAmount) * 1000);

    if (feedbackAmount < 0.41 && !analyzer.getPeak())
    {
      peaked = false;
      effects[0]->setParameter("feedback", 0.4);
      effects[1]->setParameter("feedback", 0.4);
      effects[3]->setParameter("feedback", 0.5);
      effects[3]->setParameter("DelayTime",1500);
      std::cout << "terug" << std::endl;
      effectCounter = 0;
    }
    if(counter == samplerate)
    {
    effects[0]->setParameter("modDepth", 200);
    effects[1]->setParameter("modDepth", 200);
    }
  }
}

static void processAudio()
{
  float inBuf[chunksize];
  float outBuf[chunksize * 2];

  memset(&inBuf, 0, sizeof(inBuf));

  int counter = 0;
  int counterSeconds = 6;
  do
  {
    jack.readSamples(inBuf, chunksize);
    for (unsigned int i = 0; i < chunksize; i++)
    {
      // LEFT CHANNEL
      outBuf[2 * i] = effects[1]->process(effects[3]->process(effects[2]->process(inBuf[i] * amplitude))); // effect code here

      // RIGHT CHANNEL
      outBuf[2 * i + 1] = effects[0]->process(effects[3]->process(effects[2]->process(inBuf[i] * amplitude))); // effect code here

      // TODO maybe not analyze the signal in the processAudio
      analyzer.analyseSignal(inBuf[i]);
      counter++;

      changeEffects(counter, inBuf[i]);
      if (counter >= samplerate * counterSeconds){counter = 0;}
    }
    jack.writeSamples(outBuf, chunksize * 2);
  } while (running);
}

int main(int argc, char **argv)
{
  // set the amount of interleaved jack channels
  jack.setNumberOfInputChannels(1);
  jack.setNumberOfOutputChannels(2);

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);
  jack.autoConnect();
  samplerate = jack.getSamplerate();

  // here we fill the effect vector with effects
  effects.push_back(new Chorus(0.5, false, samplerate, 0.4, false, 0.4));
  effects.push_back(new Chorus(0.5, false, samplerate, 0.4, false, 0.8));
  effects.push_back(new ReverseDelay(1, false, samplerate));
  effects.push_back(new Delay(0.5, false, samplerate, 1500, 0.5));

  // new thread
  std::thread jackThread(processAudio);

  std::cout << "\n\nPress 'q' when you want to end the program.\n";
  while (running)
  {
    switch (std::cin.get())
    {
    case 'q':
      running = false;
      break;
    }

  }
  // end the program
  jackThread.join();
  jack.end();
  for (auto effect : effects)
  {
    delete effect;
    effect = nullptr;
  }
  return 0;
} // main()
