/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 20 May 2022 5:40:10pm
    Author:  Justin Bonnet

  ==============================================================================
*/

#include "MidiProcessor.h"
#include "PluginEditor.h"


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
    processMidiInput(midiMessages);
}

void MidiProcessor::processMidiInput(const MidiBuffer& midiMessages)
{
    for (const MidiMessageMetadata currentMessage : midiMessages){
        // checking if the sysEx message has a size of 52 because thats how long a changed patch message is.
        if(currentMessage.getMessage().isNoteOn())
        {
            DBG("MIDI ON!");
            test.setValue(50);
        }
        
        if(currentMessage.getMessage().isSysEx() && currentMessage.getMessage().getSysExDataSize() == 52)
        {
            DBG("changed patch!");
            const uint8* patchData = currentMessage.getMessage().getSysExData();
            // number 22 holds the patch value for the Cutoff.
            cutOffPatchData = patchData[22];
            DBG(cutOffPatchData);
            //test.setValue(cutOffPatchData);
            //test.setValue(50);
        }
    }
}

void MidiProcessor::sendMidiMessage(const MidiMessage& message)
{
    output->sendMessageNow(message);
}

void MidiProcessor::setFreqSliderValObject(Value& ValueObject)
{
    test.referTo(ValueObject);
}
