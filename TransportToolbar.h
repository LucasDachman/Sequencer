/*
  ==============================================================================

    TransportToolbar.h
    Created: 26 Oct 2017 3:25:46pm
    Author:  Lucas

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class TransportToolbar : public Toolbar
{

	enum TransportState
	{
		Starting,
		Playing,
		Stopping,
		Stopped
	};

};