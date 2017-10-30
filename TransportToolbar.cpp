/*
  ==============================================================================

    TransportToolbar.cpp
    Created: 26 Oct 2017 3:25:46pm
    Author:  Lucas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportToolbar.h"
enum TransportState;	

void TransportToolbar::setTracks(OwnedArray<Track> * _trackArray)
{
	trackArray = _trackArray;
}

void TransportToolbar::setState(TransportState newState)
{
	currentState = newState;
}

TransportToolbar::TransportState TransportToolbar::getState()
{
	return currentState;
}

void TransportToolbar::buttonClicked(Button * button)
{
	
}

void TransportToolbar::hiResTimerCallback()
{
	for (int tracki = 0; tracki < trackArray->size(); tracki++)
	{
		Track *currentTrack = (*trackArray)[tracki];
		currentTrack->nextStep();
	}
}

