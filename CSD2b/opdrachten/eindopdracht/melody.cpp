#include "melody.h"

void Melody::generateMelody()
{   
    //needed to generate random numbers
    srand(time(NULL));
    for (int i = 0; i < noteAmount; i++)
    {
        int rnd = rand() % 30 + 50;
         Notes[i] = rnd;
    }
}

Melody::Melody()
{
generateMelody();
}

Melody::~Melody()
{
}

float Melody::getMelodyList(int count)
{
    return Notes[count];
}