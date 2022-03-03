#include "tremolo.h"
#include "effect.h"
#include "delay.h"
#include "waveShaper.h"
#include "chorus.h"
#include "uiUtilities.h"
#include <string>
#include <vector>
#include "jack_module.h"
#include <thread>
#include <unistd.h> // sleep


#define WRITE_NUM_SAMPLES 44100

// boolean is used to keep program running / turn it off
bool running = true;



// with the marcs jack abstaraction module we dont need to know Jacks buffer size
float chunksize =2048;

float samplerate=44100; // default


float amplitude = 0.5;

// create a JackModule instance
JackModule jack;

// TODO make a more efficient user input use switch case and enum class for effect types this one sucks.

  std::vector<Effect *> effects{};


static void filter()
{
float *inBuf = new float[chunksize];
  float *outBuf = new float[chunksize];
  do
  {
    jack.readSamples(inBuf, chunksize);
    for(unsigned int i = 0; i < chunksize; i ++){      
      //left channel
      outBuf[2 *i] = effects[4]->processFrame(inBuf[i] * amplitude);
      //right channel
      outBuf[2 *i+1] = effects[5]->processFrame(inBuf[i] * amplitude);
      //tick the delay
      effects[4]->tick();
      effects[5]-> tick();
    }
    jack.writeSamples(outBuf,chunksize *2);
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
  samplerate=jack.getSamplerate();


    // add effect to vector of effect pointers.
  effects.push_back(new Delay(1, true, samplerate, 400, 0.5));
  effects.push_back(new Tremolo(1, false, samplerate, 80));
  effects.push_back(new Delay(1, false, samplerate, 800, 0.5));
  effects.push_back(new WaveShaper(1,false,samplerate));

  effects.push_back(new Chorus(0.5, false, samplerate, 0.8, true, 0.8));
  effects.push_back(new Chorus(0.5, false, samplerate, 0.8, false, 0.4));
  
  effects[4]->setParameter("modDepth", 200);
  effects[5]->setParameter("modDepth", 205);


  //new thread 
    std::thread filterThread(filter);

 

  // strings for user input used later in switch case;
  std::string userEffectOnSelection;
  std::string userEffectOFFSelection;
  // keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'h' when you want to see the help menu.\n";
  while (running)
  {
    switch (std::cin.get())
    {
    case 'q':
      running = false;
      break;

    case 'h':
      std::cout << "----------------------HELP-----------------------.\n";
      std::cout << "Press 'q' when you want to quit the program.\n";
      std::cout << "Press 'a' when you want to add an effect.\n";
      std::cout << "Press 'd' when you want to remove a effect.\n";
      std::cout << "Press 's' when you want to change settings.\n";
      std::cout << "-------------------------------------------------.\n";
      break;

    case 'a':
      // add effect code
      std::cout << "Fill in the name of the effect you want to add\n";
      std::cin >> userEffectOnSelection;

      if (userEffectOnSelection == "delay")
      {
        effects[0]->setBypass(false);
        std::cout << "delay is now on\n";
      }
      if (userEffectOnSelection == "tremolo")
      {
        effects[1]->setBypass(false);
        std::cout << "tremolo is now on\n";
      }
      break;

    case 'd':
      // bypass effect code
      std::cout << "Fill in the name of the effect you want to remove\n";
      std::cin >> userEffectOFFSelection;
      if (userEffectOFFSelection == "delay")
      {
        effects[0]->setBypass(true);
        std::cout << "delay is now bypassed\n";
      }
      if (userEffectOFFSelection == "tremolo")
      {
        effects[1]->setBypass(true);
        std::cout << "tremolo is now bypassed\n";
      }
      break;

    case 's':
      std::cout << "Fill in the name of the setting you want to change\n";
      std::string userSettingSelection;
      float userSettingVal;
      std::cin >> userSettingSelection;
      std::cout << "Fill in a value\n";
      std::cin >> userSettingVal;
      for (auto effect : effects)
      {
        effect->setParameter(userSettingSelection, userSettingVal);
      }
      break;
    }
    //otherwise i get segmentation fault when closing the program
    usleep(100000);
  }
   //destroy effects
  for (auto effect : effects)
  {
    delete effect;
    effect = nullptr;
  }
  // end the program
  filterThread.join();
  jack.end();
  return 0;
} // main()