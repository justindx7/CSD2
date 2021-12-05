#include "instrument.h"
#include <iostream>

// : sound(_sound) == sound = _sound 
// const passed by const reference to avoid unnecessary copying.
Instrument::Instrument(const std::string& _name, const std::string& _sound, const int _minPitch, const int _maxPitch): name(_name), sound(_sound), 
minPitch(_minPitch), maxPitch(_maxPitch) 
{
    std::cout <<"Constructor called: Instrument(" << name << ")" << std::endl;
}
Instrument::~Instrument()
{
    std::cout <<"Destructor called" << std::endl;

}

void Instrument::play(int midiNote) 
{
    std::cout << "midiNote: "<< midiNote << std::endl;

    if(midiNote < minPitch)
    {
     std::cout << "this note is below the pitch range" << std::endl;
    }
    else if(midiNote > maxPitch)
    {
    std::cout << "this note is above the pitch range" << std::endl;
    }
    else{
    std::cout << "Instrument:" + name + " " + "Sound:" + sound +" " + "minPitch:" << minPitch << " maxPitch:" << maxPitch<<std::endl;

    }
}

