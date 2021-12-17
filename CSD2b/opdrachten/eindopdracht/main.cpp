#include <iostream>
#include <thread>
#include <vector>
#include "jack_module.h"
#include "math.h"
#include "oscillator.h"
#include "simpleSynth.h"
#include "squareSynth.h"
#include "adSynth.h"

#include "sine.h"
#include "synth.h"
#include "saw.h"
#include "square.h"
#include "writeToFile.h"
#include "melody.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

//assignFunction for telling jack what wave forms to play

void assignFunction(JackModule &jack, std::vector<Synth*> &synths)
{
  //assign a function to the JackModule::onProces
  jack.onProcess = [&synths](jack_default_audio_sample_t *inBuf,
  jack_default_audio_sample_t *outBuf, jack_nframes_t nframes)
  {
    int  interval = 0.5 * 44100;
    int frameCount = 0;
    for (unsigned int i = 0; i < nframes; i++)
    {
      frameCount++;
      outBuf[i] = 0;
      for (auto synth : synths)
      {
        synth->setMidiPitch(80.0);
        outBuf[i] += synth->getSample();
        synth->tick();

        if(frameCount > interval){
        frameCount = 0;
        }
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

  //create a vector and fill it with pointers to subclasses from Synth so you can play multiple synths at the same time
  std::vector<Synth *> synths{new SquareSynth(30)};
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

  //destroy synths
  for(auto synth: synths){
    delete synth;
    synth = nullptr;
  }
  //end the program
  return 0;
} // main()
