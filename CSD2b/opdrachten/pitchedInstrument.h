#include "instrument.h"

class pitchedInstrument : public Instrument
{  
public:
    pitchedInstrument(const std::string& name, const std::string& sound, int minPitch, int maxPitch);
    ~pitchedInstrument();
};  