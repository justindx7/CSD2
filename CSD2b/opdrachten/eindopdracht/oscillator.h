#ifndef OSCILLATOR_H
#define OSCILLATOR_H 

class Oscillator 
{

public:
    Oscillator(float frequency, double samplerate);
    // if a class has virtual functions its destructor should also be virtual
    virtual ~Oscillator();

    void setFrequency(float frequency);
    float getFrequency();

    void setSampleRate(double newSamplerate);
    double getSampleRate();

    virtual float getSample() = 0;
    virtual void tick() = 0;

private:
    float frequency;
    double samplerate;
};

#endif