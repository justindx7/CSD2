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
    void addTransposedNote(const MidiMessage& currentMessage, int samplePos);
    void addMessageToBuffer (const MidiMessage& message);
private:
    MidiBuffer sysExBuffer;
    
    MidiDeviceInfo device;
    std::unique_ptr<MidiOutput> output;
};

