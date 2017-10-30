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

class TransportComponent :	public GroupComponent,
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
	TransportComponent();
	void setTracks(OwnedArray <Track> *_trackArray);
	void setState(TransportState newState);
	TransportState getState();
	//void buttonClicked(Button * button) override;

	// Inherited from GroupComponent
	void paint(Graphics & g) override;
	void resized() override;


private:
	// members
	TransportState currentState;
	OwnedArray<Track> * trackArray;
	ScopedPointer<ArrowButton> playStopButton;

	const int playStopButtonWidth = 60;

	// Inherited via HighResolutionTimer
	virtual void hiResTimerCallback() override;
};