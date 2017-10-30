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
	setState(Stopped);

	// Play Stop Button
	playStopButton = new ArrowButton("Start", 0.0, Colours::blue);
	playStopButton->addListener(this);
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
	if (newState == Playing)
	{
		startTimer(60000 / BPM);
	}
	else if (newState == Stopped)
	{
		stopTimer();
	}
	currentState = newState;
}

void TransportComponent::buttonClicked(Button * button)
{
	if (button == playStopButton)
	{
		Logger::outputDebugString("PlayButtonPressed!!!!");
		if (currentState == Playing)
		{
			setState(Stopped);
		}
		else if (currentState == Stopped)
		{
			setState(Playing);
		}
	}
}


TransportComponent::TransportState TransportComponent::getState()
{
	return currentState;
}

void TransportComponent::setBPM(int _bpm)
{
	BPM = _bpm;
}

int TransportComponent::getBPM()
{
	return BPM;
}
void TransportComponent::hiResTimerCallback()
{
	for (int tracki = 0; tracki < trackArray->size(); tracki++)
	{
		Track *currentTrack = (*trackArray)[tracki];
		currentTrack->nextStep();
	}
}

