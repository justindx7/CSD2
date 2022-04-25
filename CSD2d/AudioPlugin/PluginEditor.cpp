#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000.0);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.setNumDecimalPlacesToDisplay(2);
    frequencySlider.onValueChange = [] {};
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true); // [4]

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("First Audio plugin", getLocalBounds(), juce::Justification::top, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto sliderLeft = 120;
    frequencySlider.setBounds(sliderLeft, 100, getWidth() - sliderLeft - 120, 120);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}