/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

const float defaultGain = 1.0f;

//==============================================================================
JuceDemoPluginAudioProcessor::JuceDemoPluginAudioProcessor(){
    // Set up some default values..
    gain = defaultGain;

    lastUIWidth = 400;
    lastUIHeight = 200;
}

//==============================================================================
JuceDemoPluginAudioProcessor::~JuceDemoPluginAudioProcessor(){ }
void JuceDemoPluginAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages){
    const int numSamples = buffer.getNumSamples();
    int channel = 0;
    
    /*
     // Go through the incoming data, and apply our gain to it...
     for(channel = 0; channel < getNumInputChannels(); ++channel){
     buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
     }*/
    
    for(channel = 0; channel < getNumInputChannels(); ++channel){
        float* channelData = buffer.getWritePointer(channel);
        
        for(int i = 0; i < numSamples; ++i){
            const float in = channelData[i];
            channelData[i] = (in * gain);
            //channelData[i] += delayData[dp];
        }
    }
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data,(because these aren't
    // guaranteed to be empty - they may contain garbage).
    for(int i = getNumInputChannels(); i < getNumOutputChannels(); ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}
//==============================================================================
int JuceDemoPluginAudioProcessor::getNumParameters(){
    return totalNumParams;
}

float JuceDemoPluginAudioProcessor::getParameter(int index){
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch(index){
        case gainParam:     return gain;
        default:            return 0.0f;
    }
}

void JuceDemoPluginAudioProcessor::setParameter(int index, float newValue){
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch(index){
        case gainParam:     gain = newValue;  break;
        default:            break;
    }
}

float JuceDemoPluginAudioProcessor::getParameterDefaultValue(int index){
    switch(index){
        case gainParam:     return defaultGain;
        default:            break;
    }
    return 0.0f;
}

const String JuceDemoPluginAudioProcessor::getParameterName(int index){
    switch(index){
        case gainParam:     return "gain";
        default:            break;
    }
    return String::empty;
}

const String JuceDemoPluginAudioProcessor::getParameterText(int index){
    return String(getParameter(index), 2);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::prepareToPlay(double sampleRate, int /*samplesPerBlock*/){
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceDemoPluginAudioProcessor::releaseResources(){
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceDemoPluginAudioProcessor::reset(){
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
}

//==============================================================================
AudioProcessorEditor* JuceDemoPluginAudioProcessor::createEditor(){
    return new JuceDemoPluginAudioProcessorEditor(*this);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::getStateInformation(MemoryBlock& destData){
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:

    // Create an outer XML element..
    XmlElement xml("MYPLUGINSETTINGS");

    // add some attributes to it..
    xml.setAttribute("uiWidth", lastUIWidth);
    xml.setAttribute("uiHeight", lastUIHeight);
    xml.setAttribute("gain", gain);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary(xml, destData);
}

void JuceDemoPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes){
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if(xmlState != nullptr){
        // make sure that it's actually our type of XML object..
        if(xmlState->hasTagName("MYPLUGINSETTINGS")){
            // ok, now pull out our parameters..
            lastUIWidth  = xmlState->getIntAttribute("uiWidth", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute("uiHeight", lastUIHeight);

            gain  =(float) xmlState->getDoubleAttribute("gain", gain);
        }
    }
}

const String JuceDemoPluginAudioProcessor::getInputChannelName(const int channelIndex) const{
    return String(channelIndex + 1);
}

const String JuceDemoPluginAudioProcessor::getOutputChannelName(const int channelIndex) const{
    return String(channelIndex + 1);
}

bool JuceDemoPluginAudioProcessor::isInputChannelStereoPair(int /*index*/) const{
    return true;
}

bool JuceDemoPluginAudioProcessor::isOutputChannelStereoPair(int /*index*/) const{
    return true;
}

bool JuceDemoPluginAudioProcessor::acceptsMidi() const{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceDemoPluginAudioProcessor::producesMidi() const{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceDemoPluginAudioProcessor::silenceInProducesSilenceOut() const{
    return false;
}

double JuceDemoPluginAudioProcessor::getTailLengthSeconds() const{
    return 0.0;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter(){
    return new JuceDemoPluginAudioProcessor();
}
