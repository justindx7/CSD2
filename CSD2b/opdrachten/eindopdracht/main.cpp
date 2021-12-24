#include <iostream>
#include <thread>
#include <vector>
#include "jack_module.h"
#include "math.h"
#include "oscillator.h"
#include "simpleSynth.h"
#include "squareSynth.h"
#include "noiseSynth.h"

#include "adSynth.h"

#include "sine.h"
#include "synth.h"
#include "saw.h"
#include "square.h"
#include "writeToFile.h"
#include "melody.h"
#include "uiUtilities.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */


//assignFunction for telling jack what synths to play
void assignFunction(JackModule &jack, std::vector<Synth *> &synths, Melody &melody)
{
  //assign a function to the JackModule::onProces
  jack.onProcess = [&synths,&melody](jack_default_audio_sample_t *inBuf,
    jack_default_audio_sample_t *outBuf, jack_nframes_t nframes)
  {
    int interval = 44100 * 0.25;
    static int frameCount = 0;
    static int melodyCount = -1;

    for (unsigned int i = 0; i < nframes; i++)
    {
      frameCount++;
      outBuf[i] = 0;
      
      //Reset melodyCounter if its longer than the MelodyArray from the melody Class
      if (melodyCount == melody.getMelodyArrayLength() - 1)
      {
        melodyCount = -1;
      }
      

      for (auto synth : synths)
      {
        outBuf[i] += synth->getSample();
        synth->tick();
      }

      //Check if the framecount >= interval and set to zero
      if (frameCount >= interval)
      {
          frameCount = 0;
          melodyCount++;
          
          //Change midipitch for all synths in the vector
          for (auto synth : synths)
          {
            synth->setMidiPitch(melody.getMelodyList(melodyCount));
          }

          //std::cout << melody.getMelodyList(melodyCount) << std::endl;
          //std::cout << melodyCount << std::endl;
      }
      //we do this because we use the amplitudes in the oscillator classes
      outBuf[i] /= synths.size();
    }
    return 0;
  };
}

void midiNoteRange()
{
  
}


int main(int argc, char **argv)
{

  //USER INPUT
  std::string synthsList[5]{"SquareSynth", "ADSynth", "SimpleSynth","NoiseSynth","All"};
  int synthChoise = UIUtilities::retrieveSelectionIndex(synthsList, 5);

  //SYNTH SELECTION
  std::vector<Synth *> synths{};
  switch(synthChoise)
  {
    case 0:
    std::cout <<"Square Synth" << std::endl;
    synths.push_back(new SquareSynth(80));
    break;

    case 1:
      std::cout <<"Additive Synth"<< std::endl;
      synths.push_back(new AdSynth(80));
    break;

    case 2:
      std::cout <<"Simple Synth" << std::endl;
      synths.push_back(new SimpleSynth(80));
    break;

    case 3:
      std::cout <<"Noise Synth" << std::endl;
      synths.push_back(new NoiseSynth(80));
    break;

    case 4:
      std::cout <<"ALL Synths" << std::endl;
      synths.push_back(new SimpleSynth(80));
      synths.push_back(new SquareSynth(80));
      synths.push_back(new AdSynth(80));
    break;
  }

  //MIDI NOTE RANGE
  std::cout << "What should the lowest midi note be?" << std::endl;
  int minMidi = UIUtilities::retrieveValueInRange(0,127);
  
  std::cout << "What should the highest midi note be?" << std::endl;
  int maxMidi = UIUtilities::retrieveValueInRange(0,127);



  // create a JackModule instance
  JackModule jack;

  // create a melody instance
  Melody melody;

  // set lowest and highest note from input and generate melody
  melody.setlowestMidiNote(minMidi);
  melody.sethighestMidiNote(maxMidi);
  melody.generateMelody();

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);

  //set a global sample rate for all synths
  Synth::setSampleRate(jack.getSamplerate());




  //create a vector and fill it with pointers to subclasses from Synth so you can play multiple synths at the same time
  assignFunction(jack, synths, melody);
  jack.autoConnect();

  //keep the program running and listen for user input, q = quit, n = new melody, h = help
  std::cout << "\n\nPress 'h' when you want to see the help menu.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
    case 'q':
      running = false;
      jack.end();
      break;

    case 'n':
      melody.generateMelody();
      std::cout << "Melody generated!\n";
    break;

    case 'h':
      std::cout << "----------------------HELP-----------------------.\n";
      std::cout << "Press 'q' when you want to quit the program.\n";
      std::cout << "Press 'n' when you want to generate a new melody.\n";
      std::cout << "-------------------------------------------------.\n";
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
  for (auto synth : synths)
  {
    delete synth;
    synth = nullptr;
  }
  //end the program
  return 0;
} 
