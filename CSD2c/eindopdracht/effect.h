#pragma once
#include <iostream>
#include <string>

class Effect 
{
public:
    Effect(float drywet, bool bypass, unsigned int samplerate);
    virtual ~Effect();

    float process(float sample);
    

     //setters getters
     void setDrywet(float _drywet);
     float getDrywet();
     void setBypass(bool _bypass);
     virtual void setParameter(std::string id, float val) =  0;
     
protected:

    virtual float applyEffect(float sample) = 0;

    float modSample = 0;
    float samplerate;

    private:
    float drywet = 1;
    bool bypass = false;

    
};
