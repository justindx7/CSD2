#pragma once
#include <iostream>

class Effect 
{
public:
    Effect(float drywet, bool bypass, unsigned int samplerate);
   virtual ~Effect();
   
    virtual float process(float sample) = 0;

protected:
    float modSignal = 0;

    private:
    float drywet;

    
};
//effect drywet number original signal 1 - drywet