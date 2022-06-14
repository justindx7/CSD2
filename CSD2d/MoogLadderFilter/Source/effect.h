/*
  ==============================================================================

    effect.h
    Created: 1 Jun 2022 12:42:31am
    Author:  Justin Bonnet

  ==============================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <JuceHeader.h>

//not making an effect pointer to ladderfilter in main because it this introduced problems.

class Effect
{
public:
    Effect(float drywet, bool bypass);
    virtual ~Effect();

    float process(float sample);
    

     //setters getters
     void setDrywet(float _drywet);
     float getDrywet();
     void setBypass(bool _bypass);
     bool getBypass();
     void setSamplerate(unsigned int _samplerate);
    
     virtual void setParameter(std::string id, float val) =  0;
    
     
protected:

    virtual float applyEffect(float sample) = 0;

    float modSample = 0;
    float samplerate;

    private:
    float drywet = 1;
    bool bypass = false;

    
};
