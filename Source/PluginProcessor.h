/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TheClockAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TheClockAudioProcessor();
    ~TheClockAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    // Transport Parameters
    std::atomic<float> beatsPerMinute;
    std::atomic<float> timeSigNumer;
    std::atomic<float> timeSigDenom;
    std::atomic<float> mins;
    std::atomic<float> secs;
    std::atomic<float> ppqPos;
    std::atomic<float> bar;
    std::atomic<float> beat;
    std::atomic<bool>  isLooping;
    
private:
    // Host Transport Info Class
    AudioPlayHead *playHead;
    AudioPlayHead::CurrentPositionInfo playHeadInfo;
    
    
    
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheClockAudioProcessor)
};
