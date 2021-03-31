/*
  ==============================================================================

    TitleHeader.cpp
    Created: 4 Feb 2021 11:47:30am
    Author:  Robert Fullum

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TitleHeader.h"

//==============================================================================
TitleHeader::TitleHeader() : backgroundColor ( Colour( (uint8)0,   (uint8)0,    (uint8)0 )   ),
                             textColor       ( Colour( (uint8)235, (uint8)52,   (uint8)222)  )
{
}

TitleHeader::~TitleHeader()
{
}

void TitleHeader::paint (juce::Graphics& g)
{
    g.fillAll   ( backgroundColor );
    g.setColour ( textColor );
    
    g.setFont   ( Font("TR-909", 45.0f, 0) );
    g.drawText  ( "FULLUMMUSIC", fullumMusicArea.reduced( 6, 0 ), Justification::right );
    
    g.setFont  ( Font("TR-909", 25.0f, 0) );
    g.drawText ( "The Clock", theClockArea.reduced( 6, 0), Justification::left );
}

void TitleHeader::resized()
{
    auto totalArea = getLocalBounds();
    
    fullumMusicArea = totalArea.removeFromRight( totalArea.getWidth() * 0.66f );
    
    Rectangle<int> pluginTitleArea = totalArea;
    
    theClockArea = pluginTitleArea;
    
}

void TitleHeader::setBackgroundColor(Colour& bg)
{
    backgroundColor = bg;
}

void TitleHeader::setTextColor(Colour& textC)
{
    textColor = textC;
}



//==============================================================================
//==============================================================================
//==============================================================================



void TitleFooter::paint(juce::Graphics& g)
{
    g.fillAll   (backgroundColor);
    g.setColour ( textColor );
    
    g.setFont  ( Font("Helvetica", 14, 0) );
    g.drawText ( "Version 1.0", versionArea.reduced( 12, 6 ), Justification::left );
    g.drawText ( "www.FullumMusic.com", urlArea.reduced( 12, 6 ), Justification::right );
}


void TitleFooter::resized()
{
    auto totalArea = getLocalBounds();
    
    versionArea = totalArea.removeFromLeft( totalArea.getWidth() * 0.5f );
    urlArea     = totalArea;
}
