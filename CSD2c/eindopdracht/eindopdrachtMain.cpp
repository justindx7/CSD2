#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h> // sleep
#include "jack_module.h"
#include "effect.h"
#include "chorus.h"
#include "analyzer.h"
#include <cmath>
#define WRITE_NUM_SAMPLES 44100
// boolean is used to keep program running / turn it off
bool running = true;

// with the marcs jack abstaraction module we dont need to know Jacks buffer size
float chunksize = 2048;

float samplerate = 44100; // default

float amplitude = 0.5;

// create a JackModule instance
JackModule jack;

std::vector<Effect *> effects{};

Analyzer analyzer(samplerate);


bool peaked= false;
int effectCounter = 0;

void changeEffects(int counter, float buf)
{
   double feedbackAmount;
   //scale counter to feedback amount
   feedbackAmount = (0.4 - 0.9)*(effectCounter)/(samplerate * 6) + 0.9;

   //round feedbackAmount to 3 decimals
   feedbackAmount = round(feedbackAmount * 1000.0 ) / 1000.0;
  
  if (analyzer.getPeak())
  {
    peaked = true;
  } 

  if(peaked)
  {
    effectCounter++;
    // 0.4  // /2.25 //117600
    effects[0]->setParameter("feedback", feedbackAmount);
    effects[1]->setParameter("feedback", feedbackAmount);

    if(feedbackAmount < 0.41)
    {
    peaked = false;
    effects[0]->setParameter("feedback", 0.4);
    effects[1]->setParameter("feedback", 0.4);
    effectCounter = 0;
    }
  }

}

static void processAudio()
{
  float *inBuf = new float[chunksize];
  float *outBuf = new float[chunksize];
  int counter = 0;
  do
  {
    jack.readSamples(inBuf, chunksize);
    for (unsigned int i = 0; i < chunksize; i++)
    {
      // LEFT CHANNEL
      outBuf[2 * i] = effects[0]->process(inBuf[i] * amplitude); // effect code here

      // RIGHT CHANNEL
      outBuf[2 * i + 1] = effects[1]->process(inBuf[i] * amplitude); // effect code here


      // TODO maybe not analyze the signal in the processAudio 
      analyzer.analyseSignal(inBuf[i]);
      counter++;

      changeEffects(counter, inBuf[i]);
      if (counter >= samplerate * 6){counter = 0;}
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
  effects.push_back(new Chorus(0.5, false, samplerate, 0.4, true, 0.4));
  effects.push_back(new Chorus(0.5, false, samplerate, 0.4, false, 0.8));

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
    // otherwise i get segmentation fault when closing the program
    usleep(100000);
  }
  // end the program
  jackThread.join();
  jack.end();
  return 0;
} // main()
