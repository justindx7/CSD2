#include "percussiveInstrument.h"

percussiveInstrument::percussiveInstrument(const std::string& name, const std::string& sound, int minPitch, int maxPitch): Instrument(name,sound,minPitch, maxPitch)
{
}

percussiveInstrument::~percussiveInstrument()
{
}

//for loop plays the instrument a set amount of time on a given note
void percussiveInstrument::roll(int amountOfRepetitions, int rollMidiNote)
{
    for(int i=0; i < amountOfRepetitions; i++)
    {
        play(rollMidiNote);
    }
}
