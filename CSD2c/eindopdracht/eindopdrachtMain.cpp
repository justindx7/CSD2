#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h> // sleep
#include "jack_module.h"
#include "effect.h"
#include "chorus.h"
#include "tremolo.h"
#include "sampleShaper.h"

#define WRITE_NUM_SAMPLES 44100

// boolean is used to keep program running / turn it off
bool running = true;

// with the marcs jack abstaraction module we dont need to know Jacks buffer size
float chunksize = 2048;

float samplerate = 44100; // default

float amplitude = 0.5;

// create a JackModule instance
JackModule jack;

std::vector <Effect *> effects{};


static void connectToJack()
{
    float *inBuf = new float[chunksize];
    float *outBuf = new float[chunksize];
    do
    {
        jack.readSamples(inBuf, chunksize);
        for (unsigned int i = 0; i < chunksize; i++)
        {

            // LEFT CHANNEL
            outBuf[2 * i] = effects[0]->process(inBuf[i] * amplitude); // effect code here

            // RIGHT CHANNEL
            outBuf[2 * i + 1] =effects[1]->process(inBuf[i] * amplitude); // effect code here

        }
        jack.writeSamples(outBuf, chunksize * 2);
    } while (running);
}

int main(int argc, char **argv)
{
  SampleShaper ss(1,false,samplerate);
  ss.setParameter("pickSample",0);
  std::cout << "ss.setParameter() - over \n";
    // set the amount of interleaved jack channels
    jack.setNumberOfInputChannels(1);
    jack.setNumberOfOutputChannels(2);

    // init the jack, use program name as JACK client name
    jack.init(argv[0]);
    jack.autoConnect();
    samplerate = jack.getSamplerate();


    //here we fill the effect vector with effects
    // effects.push_back(new Chorus(1, false,samplerate,0.5, false, 4));
    // effects.push_back(new Chorus(1, false,samplerate,0.4, true, 6));

    effects.push_back(new Tremolo(1, false,samplerate,440));
    effects.push_back(new Tremolo(1, false,samplerate,440));

    //new thread
    // std::thread jackThread(connectToJack);

  std::cout << "\n\nPress 'q' when you want to end the program.\n";
  while (running)
  {
    switch (std::cin.get())
    {
    case 'q':
      running = false;
      break;
    }
    //otherwise i get segmentation fault when closing the program
    usleep(100000);
  }
  // end the program
  // jackThread.join();
  // jack.end();
  return 0;
} // main()
