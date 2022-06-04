/*
  ==============================================================================

    OnePole.h
    Created: 3 Jun 2022 11:46:22am
    Author:  Justin Bonnet

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <JuceHeader.h>

class OnePole
{
public:

    OnePole();
    ~OnePole();
    
    float onePole(float sample);
    
    void setG(float _g);
    
private:
    float history1 = 0;
    float history2 = 0;
    
    float coefficient = 0;
    float coefficientHistory1 = 0;
    
    //variable coefficient
    float g = 0;
};



