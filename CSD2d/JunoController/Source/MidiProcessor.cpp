/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 20 May 2022 5:40:10pm
    Author:  Justin Bonnet

  ==============================================================================
*/

#include "MidiProcessor.h"


MidiProcessor::MidiProcessor()
    : device{MidiOutput::getDefaultDevice()},
      output{MidiOutput::openDevice(device.identifier)}
{
    DBG(device.name);
}

MidiProcessor::~MidiProcessor()
{
    
}
void MidiProcessor::process(MidiBuffer& midiMessages)
{
   // sysExBuffer.clear();
    processMidiInput(midiMessages);
    midiMessages.swapWith(sysExBuffer);
}

void MidiProcessor::processMidiInput(const MidiBuffer& midiMessages)
{
    for (const MidiMessageMetadata currentMessage : midiMessages){
        //Logger::writeToLog(currentMessage.getMessage().getDescription());
        if(currentMessage.getMessage().isNoteOnOrOff())
            addTransposedNote(currentMessage.getMessage(), currentMessage.samplePosition);
        
    }
}

void MidiProcessor::addTransposedNote(const MidiMessage& currentMessage, int samplePos)
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

void MidiProcessor::addMessageToBuffer (const MidiMessage& message)
{
        sysExBuffer.addEvent(message, sysExBuffer.getLastEventTime() + 1);
       // DBG(message.getDescription());
        output->sendMessageNow(message);
}
