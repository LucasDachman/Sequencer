/*
  ==============================================================================

    StepButton.h
    Created: 12 Oct 2017 7:53:56pm
    Author:  Lucas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#pragma once

class StepButtonLookAndFeel;

class StepButton : public TextButton
{
private:
	ScopedPointer <StepButtonLookAndFeel> customLookAndFeel;
	String name;
	bool isCurrent;

public:

	//functions
	StepButton(String _name);
	void toggleCurrent(bool);
	bool isCurrentStep();
};

class StepButtonLookAndFeel : public LookAndFeel_V4
{
	void drawButtonBackground(Graphics & g, Button & button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
	{
		StepButton * stepButton = reinterpret_cast<StepButton*>(&button);
		
		g.setColour(backgroundColour);
		auto r = g.getClipBounds();
		g.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), r.getHeight()/4);
		if (stepButton->isCurrentStep())
		{
			Logger::outputDebugString("current step!!!");
			if (stepButton->getToggleState())
			{
				g.setColour(findColour(TextButton::ColourIds::buttonColourId));
			}
			else
			{
				g.setColour(findColour(TextButton::ColourIds::buttonOnColourId));
			}
			g.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 10, r.getHeight() / 4);
		}
	}
};

