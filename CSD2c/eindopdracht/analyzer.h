#pragma once
#include <iostream>


class Analyzer
{
public:
    Analyzer(unsigned int samplerate);
    ~Analyzer();
    void analyseSignal(float sample);

    //setters and getters
    bool getPeak();
    void setPeakAmount(float amount);

private:
    unsigned int samplerate;
    bool peak = false;
    float peakAmount = 0.17;

};
