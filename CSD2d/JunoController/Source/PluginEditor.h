/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JunoControllerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JunoControllerAudioProcessorEditor (JunoControllerAudioProcessor&, AudioProcessorValueTreeState& Reference);
    ~JunoControllerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JunoControllerAudioProcessor& audioProcessor;
    
    AudioProcessorValueTreeState& Reference;
    
    juce::Slider frequencySlider;
    juce::Label  frequencyLabel;
    
    using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> FreqAttachment;
    
    MidiProcessor midiProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoControllerAudioProcessorEditor)
};
