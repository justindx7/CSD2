#include <thread>
#include <iostream>
#include <vector>
#include "jack_module.h"
#include "effect.h"
#include "chorus.h"
#include "analyzer.h"
#include "reverseDelay.h"
#include <cmath>
#include "delay.h"
#include "sampleShaper.h"
#include "looper.h"
#include "uiUtilities.h"
#include "tremolo.h"

#define WRITE_NUM_SAMPLES 44100
// boolean is used to keep program running / turn it off
bool running = true;

// with the marcs jack abstaraction module we dont need to know Jacks buffer size
constexpr size_t chunksize = 256;

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
    // set delay feedback high
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
    effects[3]->setParameter("delayTime", 300);
    // std::cout << (1 - feedbackAmount) * 1000 << std::endl;
    if (feedbackAmount < 0.41 && !analyzer.getPeak())
    {
      peaked = false;
      effects[0]->setParameter("feedback", 0.4);
      effects[1]->setParameter("feedback", 0.4);
      effects[3]->setParameter("feedback", 0.5);
      std::cout << "terug" << std::endl;
      effectCounter = 0;
    }
    if (counter == samplerate)
    {
      effects[0]->setParameter("modDepth", 150);
      effects[1]->setParameter("modDepth", 150);
      effects[3]->setParameter("delayTime", 1500);
    }
  }
//  if (buf >= 0.1 && buf <= 0.16)
 // {
    //effects[4]->setBypass(false);
//  }
//  else if (effects[4]->getBypass())
 // {
   // effects[4]->setBypass(true);
 // }
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
      // // LEFT CHANNEL
      outBuf[2 * i] = effects[1]->process(effects[3]->process(effects[2]->process(effects[5]->process(inBuf[i] * amplitude)))); // effect code here

      // RIGHT CHANNEL
      outBuf[2 * i + 1] = effects[0]->process(effects[3]->process(effects[2]->process(effects[4]->process(inBuf[i] * amplitude)))); // effect code here

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
  effects.push_back(new SampleShaper(0.5, false, samplerate,5));
  effects.push_back(new SampleShaper(0.5, false, samplerate,4));
  // effects.push_back(new Looper(1, true, samplerate));
  // effects.push_back(new Tremolo(1, false,samplerate,1));
  // effects.push_back(new Tremolo(1, false,samplerate,1));

  // new thread
  std::thread jackThread(processAudio);

  std::cout << "\n\nPress 'h' when you want to see the help menu.\n";
  while (running)
  {
    switch (std::cin.get())
    {
    case 'q':
      running = false;
      break;

    case 'h':
      std::cout << "----------------------HELP----------------------------------------.\n";
      std::cout << "Press 'q' when you want to quit the program.\n";
      std::cout << "Press 'e' when you want to add an switch an effect on and off.\n";
      std::cout << "Press 'l' when you want to load a loop into the looper.\n";
      std::cout << "------------------------------------------------------------------.\n";
      break;

    case 'w':
      std::cout << "Drag your sample into the terminal and press enter" << std::endl;
      effects[4]->setParameter("pickSample", 0);
      break;

    case 'e':
      std::string effectsList[6]{"ChorusL", "ChorusR", "reverseDelay", "Delay", "sampleShaper", "Looper"};
      int effectChoice = UIUtilities::retrieveSelectionIndex(effectsList, 6);
      // bypass switch
      effects[effectChoice]->setBypass(!effects[effectChoice]->getBypass());

      std::cout << effectsList[effectChoice] << " bypass:  "<< effects[effectChoice]->getBypass()<< std::endl;
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
