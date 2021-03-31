/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DisplayLabel.h"
#include "LooperAlert.h"
#include "TitleHeader.h"

//==============================================================================
/**
*/
class TheClockAudioProcessorEditor  : public juce::AudioProcessorEditor, public Timer
{
public:
    TheClockAudioProcessorEditor (TheClockAudioProcessor&);
    ~TheClockAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:    
    // Values
    DisplayLabel bpmValueLabel;
    DisplayLabel timeSigValueLabel;
    DisplayLabel totalBeatsValueLabel;
    
    LooperAlert loopAlert;
    
    DisplayLabel barValueLabel;
    DisplayLabel beatValueLabel;
    
    DisplayLabel timeValueLabel;
    

    // Value Strings
    String bpmValue;
    String timeSigValue;
    String totalBeatsValue;
    
    String barValue;
    String beatValue;
    
    String timeValue;
    
    
    // Colors
    Colour onyx;
    Colour magicMint;
    Colour orangePeel;
    
    // Header/Footer
    TitleHeader titleHeader;
    TitleFooter titleFooter;
    
    TheClockAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheClockAudioProcessorEditor)
};
