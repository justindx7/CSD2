#pragma once
#include "effect.h"

class WaveShaper : public Effect {

public:
    WaveShaper(float drywet, bool bypass, unsigned int samplerate);
    ~WaveShaper();

    float process(float sample) override;

    static float mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh);
    static float linMap(float value, int low, int high);

    void setParameter(std::string id, float val) override;
    void tick() override;

};