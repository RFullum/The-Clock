/*
  ==============================================================================

    DisplayLabel.h
    Created: 31 Mar 2021 5:40:34pm
    Author:  Robert Fullum

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DisplayLabel  : public juce::Component
{
public:
    DisplayLabel();
    ~DisplayLabel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /// Sets the  text color of the component
    void setColors(Colour& text);
    
    /// Sets the displayed text
    void setText(String& text);
    
    void setFontSize(float size);

private:
    Colour textColor;
    
    String labelText;
    
    float fontSize;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplayLabel)
};





