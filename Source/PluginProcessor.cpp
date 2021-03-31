/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheClockAudioProcessor::TheClockAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{
}

TheClockAudioProcessor::~TheClockAudioProcessor()
{
}

//==============================================================================
const juce::String TheClockAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheClockAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheClockAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheClockAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheClockAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheClockAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheClockAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheClockAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheClockAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheClockAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TheClockAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TheClockAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheClockAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheClockAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Get Transport Info from Host
    playHead = this->getPlayHead();
    if (playHead != nullptr)
    {
        playHead->getCurrentPosition(playHeadInfo);
    }
    
    // Extract Transport info from playHead to variables
    beatsPerMinute     = playHeadInfo.bpm;
    timeSigNumer       = playHeadInfo.timeSigNumerator;
    timeSigDenom       = playHeadInfo.timeSigDenominator;
    float timeSeconds  = playHeadInfo.timeInSeconds;
    ppqPos             = playHeadInfo.ppqPosition;
    float ppqBarStart  = playHeadInfo.ppqPositionOfLastBarStart;
    isLooping          = playHeadInfo.isLooping;
    
    // Compute Bars and Beats
    bar  = ( ppqBarStart / (timeSigNumer * (4.0f / timeSigDenom) ) ) + 1.0f;
    beat = fmodf( ppqPos, timeSigNumer ) + 1.0f;
    
    // Computer Minutes and Seconds
    mins = timeSeconds / 60.0f;
    secs = fmodf( timeSeconds, 60.0f );
    
    // Stock JUCE code
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
  
    
    
}

//==============================================================================
bool TheClockAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TheClockAudioProcessor::createEditor()
{
    return new TheClockAudioProcessorEditor (*this);
}

//==============================================================================
void TheClockAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TheClockAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheClockAudioProcessor();
}
