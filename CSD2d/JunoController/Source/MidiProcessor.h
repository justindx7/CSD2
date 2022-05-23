/*
  ==============================================================================

    MidiProcessor.h
    Created: 14 May 2022 3:44:51pm
    Author:  Justin Bonnet

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class MidiProcessor
{
    
public:
    MidiProcessor();
    ~MidiProcessor();
    
    void process(MidiBuffer& midiMessages);
    void processMidiInput(const MidiBuffer& midiMessages);
    void sendMidiMessage (const MidiMessage& message);
    
    void setFreqSliderValObject(const Value& ValueObject);
    
    
private:
    
    //this is used to create a midioutput
    MidiDeviceInfo device;
    std::unique_ptr<MidiOutput> output;
    
    Value test;
    int cutOffPatchData = 0;
};

