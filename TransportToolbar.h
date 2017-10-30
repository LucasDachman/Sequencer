/*
  ==============================================================================

    TransportToolbar.h
    Created: 26 Oct 2017 3:25:46pm
    Author:  Lucas

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Track.h"

class TransportToolbar : public Toolbar,
	public HighResolutionTimer
{
public:
	enum TransportState
	{
		Starting,
		Playing,
		Stopping,
		Stopped
	};
	
	// functions
	void setTracks(OwnedArray <Track> *_trackArray);
	void setState(TransportState newState);
	TransportState getState();
	void buttonClicked(Button * button) override;

private:
	// members
	TransportState currentState;
	OwnedArray<Track> * trackArray;

	// Inherited via HighResolutionTimer
	virtual void hiResTimerCallback() override;
};