#include <iostream>
#include <thread>
#include <vector>
#include "jack_module.h"
#include "math.h"
#include "oscillator.h"
#include "sine.h"
#include "square.h"
#include "writeToFile.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

//used virtual so this works
void assignFunction(JackModule &jack, std::vector<Oscillator*> &oscillators, float &amplitude)
{
 //assign a function to the JackModule::onProces
  jack.onProcess = [&oscillators, &amplitude](jack_default_audio_sample_t *inBuf,
    jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for (unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = 0;
      for (auto osc : oscillators) {
        outBuf[i] += osc->getSample() * amplitude;
        osc->tick();
      }
    }
    amplitude = 0.5;
    return 0;
  };
}


int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);
  double samplerate = jack.getSamplerate();
  std::vector<Oscillator*> oscillators { new Sine(550, samplerate), new Square(110, samplerate) };
  float amplitude = 0.15;
  assignFunction(jack, oscillators, amplitude);
  jack.autoConnect();
  
  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
    }
  }

//WRITING DATA TO FILE
WriteToFile fileWriter("output.csv", true);
  for(int i = 0; i < samplerate; i++) {
    fileWriter.write(std::to_string(sine.getSample()) + "\n");
    sine.tick();

    fileWriter.write(std::to_string(square.getSample()) + "\n");
    square.tick();
  }
  //end the program
  return 0;
} // main()
