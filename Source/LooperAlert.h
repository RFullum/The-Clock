/*
  ==============================================================================

    LooperAlert.h
    Created: 31 Mar 2021 10:54:38pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LooperAlert  : public juce::Component
{
public:
    LooperAlert();
    ~LooperAlert() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /// Call in timerCallback() passing bool if the loop is enabled or not
    void setsloop(bool looping);

private:
    Colour backgroundColor;
    Colour activeLoopColor;
    Colour textColor;
    
    
    String loop;
    bool isLooping;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LooperAlert)
};
