#include "melody.h"

void Melody::generateMelody()
{   
    //needed to generate random numbers
    srand(time(NULL));

    for (int i = 0; i < noteAmount; i++)
    {
        int rnd = rand() % ( highestMidiNote - lowestMidiNote + 1 ) + lowestMidiNote;
        notes[i] = rnd;
    }
}

Melody::Melody()
{
}

Melody::~Melody()
{
}

float Melody::getMelodyList(int count)
{
    return notes[count];
}

int Melody::getMelodyArrayLength()
{
    return noteAmount;
}

void Melody::sethighestMidiNote(int midiNote){
    highestMidiNote = midiNote;
}

void Melody::setlowestMidiNote(int midiNote){
    lowestMidiNote = midiNote;
}