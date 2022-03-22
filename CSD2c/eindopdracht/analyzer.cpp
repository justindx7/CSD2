#include "analyzer.h"

Analyzer::Analyzer(unsigned int samplerate) : samplerate(samplerate)
{}
Analyzer::~Analyzer(){}

void Analyzer::analyseSignal(float sample)
{
    (sample >= peakAmount) ? peak = true : peak = false;
    if(peak){

    }
}


bool Analyzer::getPeak(){return peak;}
float Analyzer::setPeakAmount(float amount){peakAmount = amount;}