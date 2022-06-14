/*
  ==============================================================================

    LadderFilter.cpp
    Created: 1 Jun 2022 12:44:21am
    Author:  Justin Bonnet

  ==============================================================================
*/

#include "LadderFilter.h"
#include <string>
#include "math.h"
//source for ladderfilter coeficients and blockdiagram:
//Oscillator and Filter Algorithms for Virtual Analog Synthesis Article in Computer Music Journal · June 2006 - Vesa Välimäki and Antti Huovilainen


LadderFilter::LadderFilter(float drywet, bool bypass) :
Effect(drywet, bypass)
{
    coefficient = 1/1.3;
    coefficientHistory1 = 0.3/1.3;
    gComp = 0.5;
}

LadderFilter::~LadderFilter()
{
    
}

float LadderFilter::applyEffect(float sample)
{
    //almost block diagram fig 16 look in "projectbeschrijving"
    
    float input = sample - history1;
    float comp = gComp * sample;
    
    
    float pole1 = onePole1.onePole(input);
    float pole2 = onePole2.onePole(pole1);
    float pole3 = onePole3.onePole(pole2);
    float pole4 = onePole4.onePole(pole3);

    
    modSample = pole4;
    history1 = ((pole4 - comp) * gRes) * 4;
    
    return modSample;
}



void LadderFilter::setParameter(std::string id, float val)
{
    
    if(id == "cutoff")
    {
        if(val != cutoffHistory)
        {
            cutoffFreq = val;
            omega = 2 * M_PI * (cutoffFreq/samplerate);
            g = 0.9892 * omega - 0.4342 * pow(omega,2) + 0.1381 * pow(omega,3) - 0.0202 * pow(omega,4);
            onePole1.setG(g);
            onePole2.setG(g);
            onePole3.setG(g);
            onePole4.setG(g);

        }
        // only calculate omega and g when the cutoff frequency is changed
        cutoffHistory = val;
    }
    
    if(id == "resonance")
    {
        if(val != resonanceHistory)
        {
            resonance = val;
            gRes = resonance * (1.0029 + 0.0526* omega  - 0.0926 * omega + 0.0218 * omega);
        }
        // only calculate gRes  when the cutoff frequency is changed
        resonanceHistory = val;
    }
}
