/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MoogLadderFilterAudioProcessorEditor::MoogLadderFilterAudioProcessorEditor (MoogLadderFilterAudioProcessor& p, juce::AudioProcessorValueTreeState& Reference)
: AudioProcessorEditor (&p), audioProcessor (p), Reference(Reference)
{
    addAndMakeVisible(cutoffSlider);
    cutoffAttachment.reset(new SliderAttachment (Reference, "cutoff", cutoffSlider));

    cutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    cutoffSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(cutoffSliderLabel);
    cutoffSliderLabel.setText("CutOff", dontSendNotification);
    cutoffSliderLabel.attachToComponent(&cutoffSlider, true);
    
    
    addAndMakeVisible(resonanceSlider);
    resonanceAttachment.reset(new SliderAttachment (Reference, "resonance", resonanceSlider));
    resonanceSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    addAndMakeVisible(resonanceSliderLabel);
    resonanceSliderLabel.setText("Resonance", dontSendNotification);
    resonanceSliderLabel.attachToComponent(&resonanceSlider, true);

    
    
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
}

MoogLadderFilterAudioProcessorEditor::~MoogLadderFilterAudioProcessorEditor()
{
}

//==============================================================================
void MoogLadderFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Ladder filter", getLocalBounds(), juce::Justification::topLeft, 1);
}

void MoogLadderFilterAudioProcessorEditor::resized()
{
    auto sliderLeft = 120;
    cutoffSlider.setBounds(getWidth()/4, getHeight()/2, getWidth() - sliderLeft - 120, 120);
    resonanceSlider.setBounds(getWidth()/4, getHeight()/5, getWidth() - sliderLeft - 120, 120);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
