#include "instrument.h"
#include "snare.h"
#include "guitar.h"
#include "violin.h"




int main()
{
    Snare aSnare;
    Violin aViolin;
    Guitar aGuitar;

    aSnare.play(64);
    aViolin.play(10);
    aViolin.play(88);
    aGuitar.play(64);


    aSnare.roll(3,55);

    return 0;
}
