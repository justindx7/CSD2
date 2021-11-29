#ifndef PERCUSSIVEINSTRUMENT_H
#define PERCUSSIVEINSTRUMENT_H 

#include "instrument.h"


class percussiveInstrument : public Instrument
{
public:
    percussiveInstrument(const std::string& name, const std::string& sound, int minPitch, int maxPitch);
    ~percussiveInstrument();
    void roll(int amountOfRepetitions, int rollMidiNote);
};

#endif