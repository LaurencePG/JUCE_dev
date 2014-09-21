/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_526ED7A9__
#define __PLUGINPROCESSOR_H_526ED7A9__

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
    As the name suggest, this class does the actual audio processing.
*/
class JuceDemoPluginAudioProcessor  : public AudioProcessor {
public:
    //==============================================================================
    JuceDemoPluginAudioProcessor();
    ~JuceDemoPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    
    //==============================================================================
    bool hasEditor() const override                  { return true; }
    // Base class for the component that acts as the GUI for an AudioProcessor.
    AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const String getName() const override            { return JucePlugin_Name; }

    int getNumParameters() override;
    float getParameter(int index) override;
    float getParameterDefaultValue(int index) override;
    void setParameter(int index, float newValue) override;
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;

    const String getInputChannelName(int channelIndex) const override;
    const String getOutputChannelName(int channelIndex) const override;
    bool isInputChannelStereoPair(int index) const override;
    bool isOutputChannelStereoPair(int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override                                              { return 1; }
    int getCurrentProgram() override                                           { return 0; }
    void setCurrentProgram(int /*index*/) override                             {}
    const String getProgramName(int /*index*/) override                        { return "Default"; }
    void changeProgramName(int /*index*/, const String& /*newName*/) override  {}

    //==============================================================================
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //==============================================================================
    // These properties are public so that our editor component can access them
    // A bit of a hacky way to do it, but it's only a demo! Obviously in your own
    // code you'll do this much more neatly..

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    // - Jules
    int lastUIWidth, lastUIHeight;

    //==============================================================================
    enum Parameters{
        gainParam = 0,

        totalNumParams
    };

    float gain;

private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JuceDemoPluginAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_526ED7A9__
