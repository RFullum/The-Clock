/*
  ==============================================================================

    DisplayLabel.cpp
    Created: 31 Mar 2021 5:40:34pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DisplayLabel.h"

//==============================================================================
DisplayLabel::DisplayLabel() :
    fontSize(16.0f)
{}

DisplayLabel::~DisplayLabel()
{}

void DisplayLabel::paint (juce::Graphics& g)
{
    g.fillAll ( Colours::black );

    g.setColour ( textColor );
    g.setFont   ( Font("TR-909", fontSize, Font::bold) );
    
    g.drawText ( labelText, getLocalBounds(), Justification::centred, true);
}

void DisplayLabel::resized()
{}

/// Sets the and text color of the component
void DisplayLabel::setColors(Colour &text)
{
    textColor = text;
}


void DisplayLabel::setText(String &text)
{
    labelText = text;
}


void DisplayLabel::setFontSize(float size)
{
    fontSize = size;
}
