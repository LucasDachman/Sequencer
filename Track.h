/*
  ==============================================================================

    Track.h
    Created: 13 Oct 2017 8:24:17am
    Author:  Lucas

  ==============================================================================
*/

#pragma once

#include "StepButton.h"
#include "../JuceLibraryCode/JuceHeader.h"

class Track : public Component,
	public Slider::Listener,
	public Button::Listener,
	public AudioTransportSource
{
public:
	OwnedArray<StepButton> stepButtons;

	// functions
	Track(int num_steps);
	void paint(Graphics & g) override;
	void resized() override;
	void nextStep();

private:
	int numSteps;
	int trackNum;
	float trackLevel;
	TextButton openFileButton;
	Slider trackLevelSlider;
	AudioFormatManager formatManager;
	ScopedPointer<AudioFormatReaderSource> readerSource;
	int currentStepIndex;

	// functions
	void openFileButtonClicked();

	// inherited
	void sliderValueChanged(Slider * slider) override;
	void buttonClicked(Button * button) override;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Track)

	// Inherited via AudioSource
	void getNextAudioBlock(const AudioSourceChannelInfo & bufferToFill) override;
};