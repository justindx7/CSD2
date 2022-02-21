#include "tremolo.h"
#include "effect.h"
#include "delay.h"
#include "uiUtilities.h"
#include <string>
#include <vector>





#include "writeToFile.h"
#include "jack_module.h"


#define WRITE_TO_FILE 0
#define WRITE_NUM_SAMPLES 44100

//TODO add new jack module from Marc github
//TODO make a more efficient user input use switch case and enum class for effect types this one sucks.


int main(int argc, char **argv) {

  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);
  float samplerate = jack.getSamplerate();
  float amplitude = 0.5;

  // instantiate tremolo effect
  //Effect* effect;

 // Delay effect(1, false, samplerate, 500, 0.5);
  //Tremolo effect(1, false, samplerate, 20);

  std::vector<Effect *> effects{};
  
  //add effect to vector of effect pointers and put the bypass true
  effects.push_back(new Delay(1, true, samplerate, 500, 0.5));
  effects.push_back(new Tremolo(1, true, samplerate, 200));
  
  #if WRITE_TO_FILE
        WriteToFile fileWriter("output.csv", true);
    // assign a function to the JackModule::onProces
    jack.onProcess = [&amplitude, &effect, &fileWriter](jack_default_audio_sample_t* inBuf,
      jack_default_audio_sample_t* outBuf, jack_nframes_t nframes) {

  #else
    // assign a function to the JackModule::onProces
    jack.onProcess = [&amplitude, &effects](jack_default_audio_sample_t* inBuf,
      jack_default_audio_sample_t* outBuf, jack_nframes_t nframes) {
  #endif
      for(unsigned int i = 0; i < nframes; i++) {
        for(auto effect : effects){
        outBuf[i] = effect->processFrame(inBuf[i]) * amplitude;
        effect->tick();
        }
        // ----- write result to file -----
  #if WRITE_TO_FILE
        static int count = 0;
        if(count < WRITE_NUM_SAMPLES) {ß
          fileWriter.write(std::to_string(outBuf[i]) + "\n");
        } else {
          // log 'Done' message to console, only once
          static bool loggedDone = false;
          if(!loggedDone) {
            std::cout << "\n**** DONE **** \n"
              << "Output is written to file.\n"
              << "Please enter 'q' to quit the program." << std::endl;
            loggedDone = true;
          }
        }
        count++;
        // set output to 0 to prevent issues with output
        outBuf[i] = 0;
  #endif
      }

      return 0;
    };

    jack.autoConnect();

    //strings for user input used later in switch case;
    std::string userEffectOnSelection;
    std::string userEffectOFFSelection;
    //keep the program running and listen for user input, q = quit
    std::cout << "\n\nPress 'h' when you want to see the help menu.\n";
    // boolean is used to keep program running / turn it off
    bool running = true;
    while (running)
    {
      switch (std::cin.get())
      {
        case 'q':
          running = false;
          jack.end();
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
          //add effect code
          std::cout << "Fill in the name of the effect you want to add\n";
          std::cin >> userEffectOnSelection;

          if(userEffectOnSelection == "delay"){
          effects[0]->setBypass(false);
          std::cout << "delay is now on\n";
          }
          if(userEffectOnSelection == "tremolo"){
          effects[1]->setBypass(false);
          std::cout << "tremolo is now on\n";
          }
          break;

        case 'd':
          //delete effect code
          std::cout << "Fill in the name of the effect you want to remove\n";
          std::cin >> userEffectOFFSelection;
          if(userEffectOFFSelection == "delay"){
          effects[0]->setBypass(true);
          std::cout << "delay is now bypassed\n";

          }
          if(userEffectOFFSelection == "tremolo"){
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
          for(auto effect : effects){
          effect->setParameter(userSettingSelection, userSettingVal);
          }
          break;
        }

    }

    //end the program
    return 0;

  } // main()