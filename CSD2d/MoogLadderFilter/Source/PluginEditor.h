/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LadderFilter.h"

//==============================================================================
/**
*/
class MoogLadderFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    
    MoogLadderFilterAudioProcessorEditor (MoogLadderFilterAudioProcessor&, juce::AudioProcessorValueTreeState& Reference);
    ~MoogLadderFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MoogLadderFilterAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& Reference;

    
    Slider cutoffSlider;
    Label cutoffSliderLabel;
    std::unique_ptr<SliderAttachment> cutoffAttachment;

    
    Slider resonanceSlider;
    Label resonanceSliderLabel;
    std::unique_ptr<SliderAttachment> resonanceAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoogLadderFilterAudioProcessorEditor)
};
