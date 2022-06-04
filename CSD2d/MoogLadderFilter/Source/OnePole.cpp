/*
  ==============================================================================

    OnePole.cpp
    Created: 3 Jun 2022 11:46:11am
    Author:  Justin Bonnet

  ==============================================================================
*/

#include "OnePole.h"

OnePole::OnePole()
{
    coefficient = 1/1.3;
    coefficientHistory1 = 0.3/1.3;    
}

OnePole::~OnePole()
{
}

float OnePole::onePole(float sample)
{
    //block diagram fig 14
    float onePoleResult = ((sample * coefficient + history1) - history2) * g + history2;
    history1 = sample * coefficientHistory1;
    history2 = onePoleResult;
    
    return onePoleResult;
}


void OnePole::setG(float _g)
{
    g = _g;
}
