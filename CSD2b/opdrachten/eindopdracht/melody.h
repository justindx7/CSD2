#include <iostream>
#include <ctime>
#include <random>

class Melody
{
public:
    Melody();
    ~Melody();

float getMelodyList(int count);
void generateMelody();
int getMelodyArrayLength();

//SETTERS
void sethighestMidiNote(int midiNote);
void setlowestMidiNote(int midiNote);


private:
 int noteAmount = 8;

 int highestMidiNote = 0;
 int lowestMidiNote = 0;

int notes[8] = {};

};