/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheClockAudioProcessorEditor::TheClockAudioProcessorEditor (TheClockAudioProcessor& p)
    : AudioProcessorEditor (&p),
      onyx                   ( Colour( (uint8)53,  (uint8)59,  (uint8)60  ) ),
      magicMint              ( Colour( (uint8)174, (uint8)255, (uint8)216 ) ),
      orangePeel             ( Colour( (uint8)252, (uint8)152, (uint8)0   ) ),
      audioProcessor (p)
{
    setSize (1200, 500);
    
    Timer::startTimerHz( 60 );
    
    // Left Column Values
    bpmValueLabel.setColors        ( magicMint );
    timeSigValueLabel.setColors    ( magicMint );
    totalBeatsValueLabel.setColors ( magicMint );
    
    bpmValueLabel.setFontSize        ( 60.0f );
    timeSigValueLabel.setFontSize    ( 60.0f );
    totalBeatsValueLabel.setFontSize ( 60.0f );
    
    addAndMakeVisible ( bpmValueLabel        );
    addAndMakeVisible ( timeSigValueLabel    );
    addAndMakeVisible ( totalBeatsValueLabel );
    
    // Loop Alert
    addAndMakeVisible ( loopAlert );
    
    // Bars & Beats
    barValueLabel.setColors  ( magicMint );
    beatValueLabel.setColors ( magicMint );
    
    barValueLabel.setFontSize  ( 100.0f );
    beatValueLabel.setFontSize ( 100.0f );
    
    addAndMakeVisible ( barValueLabel  );
    addAndMakeVisible ( beatValueLabel );
    
    // Minutes & Seconds
    timeValueLabel.setColors   ( magicMint );
    timeValueLabel.setFontSize ( 120.0f    );
    
    addAndMakeVisible ( timeValueLabel );
    
    // Header/Footer
    titleHeader.setTextColor ( orangePeel );
    titleFooter.setTextColor ( orangePeel );
    
    addAndMakeVisible ( titleHeader );
    addAndMakeVisible ( titleFooter );
}

TheClockAudioProcessorEditor::~TheClockAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void TheClockAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll( onyx );
}

void TheClockAudioProcessorEditor::resized()
{
    int  sectionSpacer = 2;
    auto totalArea     = getLocalBounds().reduced( sectionSpacer );
    
    // Header
    Rectangle<int> titleHeaderArea = totalArea.removeFromTop ( 55.0f ).reduced ( sectionSpacer );
    
    titleHeader.setBounds ( titleHeaderArea );
    
    // Footer
    Rectangle<int> titleFooterArea = totalArea.removeFromBottom ( 30.0f ).reduced ( sectionSpacer );
    
    titleFooter.setBounds ( titleFooterArea );
    
    // Main Sections
    Rectangle<int> leftColumn  = totalArea.removeFromLeft( totalArea.getWidth() * 0.25f );
    Rectangle<int> rightColumn = totalArea;
    
    
    // Left Column
    float leftSectionHeight = leftColumn.getHeight() / 4.0f;
    
    Rectangle<int> bpmArea        = leftColumn.removeFromTop ( leftSectionHeight ).reduced ( sectionSpacer );
    Rectangle<int> timeSigArea    = leftColumn.removeFromTop ( leftSectionHeight ).reduced ( sectionSpacer );
    Rectangle<int> totalBeatsArea = leftColumn.removeFromTop ( leftSectionHeight ).reduced ( sectionSpacer );
    Rectangle<int> loopingArea    = leftColumn.reduced       ( sectionSpacer );
    
    bpmValueLabel.setBounds        ( bpmArea        );
    timeSigValueLabel.setBounds    ( timeSigArea    );
    totalBeatsValueLabel.setBounds ( totalBeatsArea );
    
    loopAlert.setBounds ( loopingArea );
    
    // Right Column
    float rightSectionHeight = rightColumn.getHeight() * 0.5f;
    
    Rectangle<int> barBeatArea = rightColumn.removeFromTop  ( rightSectionHeight );
    Rectangle<int> barArea     = barBeatArea.removeFromLeft ( barBeatArea.getWidth() * 0.5f ).reduced( sectionSpacer );
    Rectangle<int> beatArea    = barBeatArea.reduced        ( sectionSpacer );
    
    barValueLabel.setBounds  ( barArea  );
    beatValueLabel.setBounds ( beatArea );
    
    Rectangle<int> timeValueArea = rightColumn.reduced ( sectionSpacer );
    
    timeValueLabel.setBounds( timeValueArea );
    
}


void TheClockAudioProcessorEditor::timerCallback()
{
    bpmValue        = String( audioProcessor.beatsPerMinute );
    totalBeatsValue = String( (int)audioProcessor.ppqPos );
    
    timeSigValue = String( audioProcessor.timeSigNumer );
    timeSigValue.append ( "/", 1 );
    timeSigValue.append ( String( audioProcessor.timeSigDenom ), 2 );
    
    bpmValueLabel.setText        ( bpmValue        );
    timeSigValueLabel.setText    ( timeSigValue    );
    totalBeatsValueLabel.setText ( totalBeatsValue );
    
    loopAlert.setsloop ( audioProcessor.isLooping );
    
    barValue  = String( (int)audioProcessor.bar  );
    beatValue = String( (int)audioProcessor.beat );
    
    barValueLabel.setText  ( barValue  );
    beatValueLabel.setText ( beatValue );
    
    String seconds;
    
    if (audioProcessor.secs < 10.0f )
    {
        seconds = String("0");
        seconds.append( String( (int)audioProcessor.secs ), 1);
    }
    else
    {
        seconds = String( (int)audioProcessor.secs );
    }
    
    timeValue = String ( (int)audioProcessor.mins );
    timeValue.append ( ":", 1 );
    timeValue.append   ( seconds, 2 );
    
    timeValueLabel.setText ( timeValue );
    
    repaint();
}

