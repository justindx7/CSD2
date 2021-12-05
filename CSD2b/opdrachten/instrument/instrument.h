#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_ 
#include <iostream>
#include <string>


class Instrument 
{
public:
    Instrument(const std::string& _name, const std::string& _sound, int _minPitch, int _maxPitch);
    ~Instrument();
    void play(int midiNote);
    
//this is private so you cant acces it outside the class
private:
    std::string sound;
    std::string name;
    int minPitch;
    int maxPitch;

};
#endif