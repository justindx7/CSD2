#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

//used virtual so this works
void assignFunction(JackModule &jack, Oscillator &oscillator, float &amplitude)
{
 //assign a function to the JackModule::onProces
  jack.onProcess = [&oscillator, &amplitude](jack_default_audio_sample_t *inBuf,
    jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = oscillator.getSample() * amplitude;
      oscillator.tick();
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
  Sine sine (220, samplerate);
  
  float amplitude = 0.15;
 
  assignFunction(jack, sine, amplitude);

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

  //end the program
  return 0;
} // main()
