/*
  ==============================================================================

    LooperAlert.cpp
    Created: 31 Mar 2021 10:54:38pm
    Author:  Robert Fullum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LooperAlert.h"

//==============================================================================
LooperAlert::LooperAlert() :
    backgroundColor ( Colours::black ),
    activeLoopColor ( Colour( (uint8)57, (uint8)250, (uint8)40) ),
    textColor       ( activeLoopColor.contrasting() ),
    loop            ( "LOOP" ),
    isLooping       ( false  )
{}

LooperAlert::~LooperAlert()
{
}

void LooperAlert::paint (juce::Graphics& g)
{
    // Fills with green and "LOOP" when loop is active, otherwise black.
    if (isLooping)
    {
        g.fillAll( activeLoopColor );
        g.setColour( textColor );
        g.setFont   ( Font("TR-909", 60.0f, Font::bold) );
        g.drawText ( loop, getLocalBounds(), Justification::centred, true);
    }
    else
    {
        g.fillAll ( backgroundColor );
    }
}

void LooperAlert::resized()
{}


/// Call in timerCallback() passing bool if the loop is enabled or not
void LooperAlert::setsloop(bool looping)
{
    isLooping = looping;
}
