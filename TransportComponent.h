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
#include "TransportController.h"

class TransportController;

class TransportComponent :	public GroupComponent,
							Button::Listener,
							Slider::Listener,
							ComboBox::Listener
{
public:

	// functions
	TransportComponent();
	TransportComponent(TransportController *);

	// Inherited from GroupComponent
	void paint(Graphics & g) override;
	void resized() override;


private:
	// members
	ScopedPointer<ArrowButton> playStopButton;
	Slider bpmSlider;
	ComboBox multiplierBox;

	TransportController * transportController;

	const int playStopButtonWidth = 60;
	const int minBPM = 50;
	const int maxBPM = 280;
	const float bpmSliderInterval = 0.5;
	const int bpmSliderWidth = 150;

	// Functions
	void setUp();

	// Inherited via Listener
	virtual void buttonClicked(Button *) override;
	virtual void sliderValueChanged(Slider *) override;

	// Inherited via Listener
	virtual void comboBoxChanged(ComboBox * comboBoxThatHasChanged) override;
};