/*
  ==============================================================================

    TransportToolbar.cpp
    Created: 26 Oct 2017 3:25:46pm
    Author:  Lucas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransportComponent.h"
//enum TransportState;	

TransportComponent::TransportComponent()
{
	setUp();
}

TransportComponent::TransportComponent(TransportController * _controller)
{
	transportController = _controller;
	setUp();
}

void TransportComponent::setUp()
{
	// Play Stop Button
	playStopButton = new ArrowButton("Start", 0.0, Colours::blue);
	playStopButton->addListener(this);
	addAndMakeVisible(playStopButton);

	// BPM Slider
	bpmSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	bpmSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	bpmSlider.setRange(minBPM, maxBPM, bpmSliderInterval);
	bpmSlider.addListener(this);
	addAndMakeVisible(bpmSlider);

	transportController->setBPM(bpmSlider.getValue());
}

void TransportComponent::paint(Graphics & g)
{
	g.fillAll(Colours::lightgrey);
}

void TransportComponent::resized()
{
	int border = 10;
	auto r = getLocalBounds();

	auto playButtonArea = r.removeFromLeft(playStopButtonWidth);
	playStopButton->setBounds(playButtonArea.reduced(border));

	auto rightSide = r.removeFromRight(r.getWidth() / 2);
	auto bpmSliderArea = rightSide.removeFromLeft(bpmSliderWidth);
	bpmSlider.setBounds(bpmSliderArea.reduced(border));
}

void TransportComponent::buttonClicked(Button * button)
{
	if (button == playStopButton)
	{
		Logger::outputDebugString("PlayButtonPressed!!!!");
		if (transportController->getState() == TransportController::Playing)
		{
			transportController->setState(TransportController::Stopped);
		}
		else if (transportController->getState() == TransportController::Stopped)
		{
			transportController->setState(TransportController::Playing);
		}
	}
}

void TransportComponent::sliderValueChanged(Slider * slider)
{
	if (slider == &bpmSlider)
	{
		transportController->setBPM(slider->getValue());
	}
}


