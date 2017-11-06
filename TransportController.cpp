/*
  ==============================================================================

    TransportController.cpp
    Created: 1 Nov 2017 1:41:26pm
    Author:  Lucas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportController.h"
#include "Track.h"

TransportController::TransportController()
	: currentState(Stopped)
{

}

void TransportController::setTracks(OwnedArray<Track> * _trackArray)
{
	trackArray = _trackArray;
	for (int track = 0; track < trackArray->size(); track++) 
	{
		addInputSource((*trackArray)[track], true);
	}
}

void TransportController::setState(TransportState newState)
{
	/*if (newState == Playing)
	{
		startTimer(60000 / BPM);
	}
	else if (newState == Stopped)
	{
		stopTimer();
	}*/
	currentState = newState;
}

TransportController::TransportState TransportController::getState()
{
	return currentState;
}

void TransportController::setBPM(int _bpm)
{
	BPM = _bpm;
	if (currentState == Playing)
	{
		startTransport();
	}
}

int TransportController::getBPM()
{
	return BPM;
}

void TransportController::startTransport()
{
	startTimer(60000 / BPM);
}

void TransportController::hiResTimerCallback()
{
	if (currentState == Playing)
	{
		for (int tracki = 0; tracki < trackArray->size(); tracki++)
		{
			Track *currentTrack = (*trackArray)[tracki];
			currentTrack->nextStep();
		}
	}
}

