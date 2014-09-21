/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor(JuceDemoPluginAudioProcessor& owner)
    : AudioProcessorEditor (owner),
      infoLabel(String::empty),
      gainLabel("", "Volume:"),
      gainSlider("gain")
{
    // add some sliders..
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::Rotary);
    gainSlider.addListener(this);
    gainSlider.setRange(0.0, 1.0, 0.01);

    // add some labels for the sliders..
    gainLabel.attachToComponent(&gainSlider, false);
    
    // add a label that will display the current timecode and status..
    addAndMakeVisible(infoLabel);
    infoLabel.setColour(Label::textColourId, Colours::blue);

    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
    resizeLimits.setSizeLimits(150, 150, 800, 300);

    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize(owner.lastUIWidth,
            owner.lastUIHeight);

    startTimer(50); // uSeconds
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint(Graphics& g){
    g.setGradientFill(ColourGradient(Colours::white, 0, 0,
                                     Colours::grey, 0, (float)getHeight(), false));
    g.fillAll();
}

void JuceDemoPluginAudioProcessorEditor::resized(){
    infoLabel.setBounds(10, 4, 400, 25);
    gainSlider.setBounds(20, 60, 150, 40);

    resizer->setBounds(getWidth()-16, getHeight()-16, 16, 16);

    getProcessor().lastUIWidth = getWidth();
    getProcessor().lastUIHeight = getHeight();
}

//==============================================================================
// This timer periodically checks whether any of the filter's parameters have changed...
void JuceDemoPluginAudioProcessorEditor::timerCallback(){
    JuceDemoPluginAudioProcessor& ourProcessor = getProcessor();

    gainSlider.setValue(ourProcessor.gain, dontSendNotification);
}

// This is our Slider::Listener callback, when the user drags a slider.
void JuceDemoPluginAudioProcessorEditor::sliderValueChanged(Slider* slider){
    if(slider == &gainSlider){
        // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
        // by the host, rather than just modifying them directly, otherwise the host won't know
        // that they've changed.
        getProcessor().setParameterNotifyingHost(JuceDemoPluginAudioProcessor::gainParam,
                                                (float)gainSlider.getValue());
    }
}

//==============================================================================
