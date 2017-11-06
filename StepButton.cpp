/*
  ==============================================================================

    StepButton.cpp
    Created: 12 Oct 2017 7:53:56pm
    Author:  Lucas

  ==============================================================================
*/

#include "StepButton.h"
#include "../JuceLibraryCode/JuceHeader.h"

StepButton::StepButton(String _name = "Default")
{
	name = _name;
	isCurrent = false;
	setClickingTogglesState(true);
	setButtonText(name);
}

void StepButton::toggleCurrent(bool x)
{
	isCurrent = x;
}

bool StepButton::isCurrentStep()
{
	return isCurrent;
}