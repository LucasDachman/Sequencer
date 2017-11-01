/*
  ==============================================================================

    TransportController.h
    Created: 1 Nov 2017 1:41:26pm
    Author:  Lucas

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Track.h"

class TransportController :		public HighResolutionTimer,
								public MixerAudioSource
{

public:
	enum TransportState
	{
		Starting,
		Playing,
		Stopping,
		Stopped
	};

	TransportController();
	void setBPM(int _bpm);
	int getBPM();
	void setTracks(OwnedArray<Track> *_trackArray);
	void setState(TransportState newState);
	TransportState getState();
	void startTransport();

private:
	
	TransportState currentState;
	OwnedArray<Track> * trackArray;

	int BPM;
	// Inherited via HighResolutionTimer
	virtual void hiResTimerCallback() override;
};