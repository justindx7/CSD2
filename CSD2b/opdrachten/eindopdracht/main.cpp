#include <iostream>
#include <thread>
#include <vector>
#include "jack_module.h"
#include "math.h"
#include "oscillator.h"
#include "simpleSynth.h"
#include "squareSynth.h"
#include "sine.h"
#include "synth.h"
#include "saw.h"
#include "square.h"
#include "writeToFile.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

//assignFunction for telling jack what wave forms to play

void assignFunction(JackModule &jack, std::vector<Synth *> &synths)
{
  //assign a function to the JackModule::onProces
  jack.onProcess = [&synths](jack_default_audio_sample_t *inBuf,
                             jack_default_audio_sample_t *outBuf, jack_nframes_t nframes)
  {
    for (unsigned int i = 0; i < nframes; i++)
    {
      outBuf[i] = 0;
      for (auto synth : synths)
      {
        outBuf[i] += synth->getSample();
        synth->tick();
      }
      //we do this because we use the amplitudes in the oscillator classes
      outBuf[i] /= synths.size();
    }
    return 0;
  };
}

int main(int argc, char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);

  //set a global sample rate for all synths
  Synth::setSampleRate(jack.getSamplerate());

  SquareSynth squareSynth(60);

  //create a vector and fill it with pointers to subclasses from Synth so you can play multiple synths at the same time
  std::vector<Synth *> synths{new SimpleSynth(65), new SquareSynth(60)};
  assignFunction(jack, synths);
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


  // Print wave form how its played
  for (int i = 0; i < 500; i++)
  {
    for (auto synth : synths)
    {
      double sample = synth->getSample();
      fileWriter.write(std::to_string(sample) + "\n");
      std::cout << sample << " ";
      synth->tick();
    }
  }
// Print wave that are played after one a nother
  for (auto synth : synths)
  {
    for (int i = 0; i < 500; i++)
    {
      double sample = synth->getSample();
      fileWriter.write(std::to_string(sample) + "\n");
      std::cout << sample << " ";
      synth->tick();
    }
  }
  std::cout << std::endl;
  //end the program
  return 0;
} // main()
