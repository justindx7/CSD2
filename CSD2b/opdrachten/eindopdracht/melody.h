#include <iostream>
#include <ctime>

class Melody
{
public:
    Melody();
    ~Melody();

float getMelodyList(int count);
void generateMelody();

private:
 int noteAmount = 8;

 float Notes[8] = {};

};