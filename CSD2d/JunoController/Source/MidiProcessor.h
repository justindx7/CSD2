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
    
    int sliderVal = 0;
   
    
    void setSliderVal(int _sliderVal)
    {
        sliderVal = _sliderVal;
    }
    
public:
    void process(MidiBuffer& midiMessages)
    {
       // sysExBuffer.clear();
        processMidiInput(midiMessages);
        midiMessages.swapWith(sysExBuffer);
        
        
        
        
        
    }
    
    void processMidiInput(const MidiBuffer& midiMessages)
    {
        for (const MidiMessageMetadata currentMessage : midiMessages){
            //Logger::writeToLog(currentMessage.getMessage().getDescription());
            if(currentMessage.getMessage().isNoteOnOrOff())
                addTransposedNote(currentMessage.getMessage(), currentMessage.samplePosition);
            
        }
    }
    
    void addTransposedNote(const MidiMessage& currentMessage, int samplePos)
    {
        auto transposedMessage = currentMessage;
        auto oldNoteNum = transposedMessage.getNoteNumber();
        transposedMessage.setNoteNumber(oldNoteNum + 7);
        
        sysExBuffer.addEvent(transposedMessage, samplePos);
        
        //uint8 cutoff[8] = {0x41, 0x36, 0x00, 0x23, 0x20, 0x01, 0x10, 0x00};
        //cutoff[7] = 100;
        //auto message = MidiMessage::createSysExMessage(cutoff, 8);
        
        //sysExBuffer.addEvent(message, samplePos);

        
    }
    
    void addMessageToBuffer (const MidiMessage& message)
    {
            sysExBuffer.addEvent(message, sysExBuffer.getLastEventTime() + 1);
            //processMidiInput(sysExBuffer);
        //MidiOut.sendMessageNow(message);
    }
    //MidiOutput midiOut;
    MidiBuffer sysExBuffer;
};

