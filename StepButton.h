/*
  ==============================================================================

    StepButton.h
    Created: 12 Oct 2017 7:53:56pm
    Author:  Lucas

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
//#include "SequencerLookAndFeel.h"


class StepButton : public TextButton
{
private:
//	ScopedPointer <SequencerLookAndFeel> customLookAndFeel;
	String name;
	bool isCurrent;

public:

	//functions
	StepButton(String _name);
	void toggleCurrent(bool);
	bool isCurrentStep();
};

