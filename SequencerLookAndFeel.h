/*
  ==============================================================================

    SequencerLookAndFeel.h
    Created: 5 Nov 2017 5:02:14pm
    Author:  Lucas

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include "StepButton.h"

class StepButton;

class SequencerLookAndFeel : public LookAndFeel_V4
{
public:

	Colour PRIMARY_COLOUR = Colours::royalblue;
	Colour SECONDARY_COLOUR = Colours::lightgrey;

	SequencerLookAndFeel()
	{
		setColour(TextButton::ColourIds::buttonColourId, PRIMARY_COLOUR);
	}

	void drawButtonBackground(Graphics & g, Button & button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
	{
		StepButton * stepButton = reinterpret_cast<StepButton*>(&button);
		
		g.setColour(backgroundColour);
		auto r = g.getClipBounds();
		g.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), r.getHeight()/4);
		if (stepButton->isCurrentStep())
		{
			stepButton->getToggleState() ? 
				g.setColour(findColour(TextButton::ColourIds::buttonColourId)) : g.setColour(findColour(TextButton::ColourIds::buttonOnColourId));

			//g.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 10, r.getHeight() / 4);
			g.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), r.getHeight() / 4, 10);
		}
	}
};

