#include <thread>
#include <iostream>

#include <unistd.h> // sleep
#include "jack_module.h"


#define WRITE_NUM_SAMPLES 44100

// boolean is used to keep program running / turn it off
bool running = true;

// with the marcs jack abstaraction module we dont need to know Jacks buffer size
float chunksize = 2048;

float samplerate = 44100; // default

float amplitude = 0.5;

// create a JackModule instance
JackModule jack;

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
            outBuf[2 * i] = inBuf[i]; // effect code here

            // RIGHT CHANNEL
            outBuf[2 * i + 1] = inBuf[i]; // effect code here

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

    //new thread 
    std::thread jackThread(connectToJack);

    // for later here we can fill the effect vector

    //

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
  jackThread.join();
  jack.end();
  return 0;
} // main()
