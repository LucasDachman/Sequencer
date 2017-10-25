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
	customLookAndFeel = new StepButtonLookAndFeel();
	setClickingTogglesState(true);
	setButtonText(name);
	TextButton::setColour(TextButton::ColourIds::buttonColourId, Colours::royalblue);
	TextButton::setLookAndFeel(customLookAndFeel);

}

void StepButton::toggleCurrent(bool x)
{
	isCurrent = x;
}

bool StepButton::isCurrentStep()
{
	return isCurrent;
}