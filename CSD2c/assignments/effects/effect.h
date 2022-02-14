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
    float drywet = 1;

    private:
    bool bypass = false;

    
};
//effect drywet number original signal 1 - drywet