/*
  ==============================================================================

    TransportToolbar.cpp
    Created: 26 Oct 2017 3:25:46pm
    Author:  Lucas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportComponent.h"
enum TransportState;	

TransportComponent::TransportComponent()
{
	playStopButton = new ArrowButton("Start", 0.0, Colours::blue);
	addAndMakeVisible(playStopButton);
}

void TransportComponent::paint(Graphics & g)
{
	g.fillAll(Colours::lightgrey);
}

void TransportComponent::resized()
{
	int border = 10;
	auto r = getLocalBounds();
	auto playButtonArea = r.removeFromLeft(playStopButtonWidth);
	playStopButton->setBounds(playButtonArea.reduced(border));
}


void TransportComponent::setTracks(OwnedArray<Track> * _trackArray)
{
	trackArray = _trackArray;
}

void TransportComponent::setState(TransportState newState)
{
	currentState = newState;
}

TransportComponent::TransportState TransportComponent::getState()
{
	return currentState;
}

void TransportComponent::hiResTimerCallback()
{
	for (int tracki = 0; tracki < trackArray->size(); tracki++)
	{
		Track *currentTrack = (*trackArray)[tracki];
		currentTrack->nextStep();
	}
}

