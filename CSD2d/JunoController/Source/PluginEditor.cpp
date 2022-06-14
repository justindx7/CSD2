/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JunoControllerAudioProcessorEditor::JunoControllerAudioProcessorEditor (JunoControllerAudioProcessor& p, AudioProcessorValueTreeState& Reference)
    : AudioProcessorEditor (&p), audioProcessor (p), Reference(Reference)
{
    addAndMakeVisible(frequencySlider);
    FreqAttachment = std::make_unique<SliderAttachment>(Reference,"cutoff", frequencySlider);
    frequencySlider.onValueChange = [this] ()
    {
        // creates midi sysexMessage this string is for the cutoff frequency
        uint8 cutoff[8] = {0x41, 0x36, 0x00, 0x23, 0x20, 0x01, 0x10, 0x00};
        cutoff[7] = frequencySlider.getValue();
        auto message = MidiMessage::createSysExMessage(cutoff, 8);
        midiProcessor.sendMidiMessage(message);
    };
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);
    
    
    midiProcessor.setFreqSliderValObject(frequencySlider.getValueObject());

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

JunoControllerAudioProcessorEditor::~JunoControllerAudioProcessorEditor()
{
}

//==============================================================================
void JunoControllerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Alpha Juno Controller", getLocalBounds(), juce::Justification::top, 1);
}

void JunoControllerAudioProcessorEditor::resized()
{
    auto sliderLeft = 120;
    frequencySlider.setBounds(sliderLeft, 100, getWidth() - sliderLeft - 120, 120);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
