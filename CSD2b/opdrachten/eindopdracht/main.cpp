#include <iostream>
#include <thread>
#include <vector>
#include "jack_module.h"
#include "math.h"
#include "oscillator.h"
#include "simpleSynth.h"
#include "sine.h"
#include "writeToFile.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

//assignFunction for telling jack what wave forms to play
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

  Synth::setSampleRate(jack.getSamplerate());
  auto oscillator = new Sine(440);
  SimpleSynth simple(64, oscillator);

  //create a vector and fill it with pointers to subclasses from Oscillator

  std::vector<Oscillator*> oscillators { oscillator };
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

  for (auto osc : oscillators)
  {
    for (int i = 0; i < Synth::getSampleRate(); i++)
    {
      fileWriter.write(std::to_string(osc->getSample()) + "\n");
      osc->tick();
    }
  }
  //CALLING destructors
  //end the program
  return 0;
} // main()
