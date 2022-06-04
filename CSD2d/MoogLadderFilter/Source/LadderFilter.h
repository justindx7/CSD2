/*
  ==============================================================================

    LadderFilter.h
    Created: 1 Jun 2022 12:44:59am
    Author:  Justin Bonnet

  ==============================================================================
*/

#pragma once
#include <iostream>
#include "effect.h"
#include "OnePole.h"


class LadderFilter : public Effect
{
public:
  LadderFilter(float drywet, bool bypass);
    LadderFilter();
  ~LadderFilter();

  float applyEffect(float sample) override;
  void setParameter(std::string id, float val) override;
        
private:

  float history1 = 0;
  float history2 = 0;

  float coefficient = 0;
  float coefficientHistory1 = 0;
  

  float g;
  float omega;
  float cutoffFreq;
  float resonance;
  float gRes = 0;
  float gComp;
    
    
  float cutoffHistory = 0;
  float resonanceHistory = 0;
    
  OnePole onePole1;
  OnePole onePole2;
  OnePole onePole3;
  OnePole onePole4;
    
};


