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

