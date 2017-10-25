/*
  ==============================================================================

    Track.cpp
    Created: 13 Oct 2017 8:24:17am
    Author:  Lucas

  ==============================================================================
*/

#include "Track.h"

Track::Track(int _numSteps)
{
	numSteps = _numSteps;
	currentStepIndex = 0;

	// Format Manager for opening files
	formatManager.registerBasicFormats();

	// Track Level Slider
	trackLevelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	trackLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 10);
	trackLevelSlider.setRange(0.0, 1.0, 0);
	trackLevelSlider.addListener(this);
	trackLevelSlider.setValue(0.75, juce::sendNotification);
	addAndMakeVisible(trackLevelSlider);

	// Track Open File Button
	openFileButton.setButtonText("Open");
	openFileButton.addListener(this);
	addAndMakeVisible(openFileButton);

	// Create Step objs and make visible
	for (int step = 0; step < numSteps; step++)
	{
		stepButtons.add(new StepButton(String(step)));
		addAndMakeVisible(stepButtons.getLast());
		stepButtons.getLast()->addListener(this);
	}
}

void Track::paint(Graphics & g)
{
	g.fillAll(Colours::lightgrey);
	g.setColour(Colours::black);
	g.drawRect(getLocalBounds());
}

void Track::resized()
{
	auto r = getLocalBounds();
	int boarderSize = 20;

	auto leftSide = r.removeFromLeft(100);
	openFileButton.setBounds(leftSide.removeFromBottom(leftSide.getHeight() / 4).reduced(5));
	trackLevelSlider.setBounds(leftSide);

	int buttonWidth = r.getWidth() / numSteps;
	
	// Draw step buttons
	for (int step = 0; step < numSteps; step++)
	{
		//Rectangle<int> bounds(buttonWidth*step, 0, buttonWidth, r.getHeight());
		Rectangle<int> bounds(r.removeFromLeft(buttonWidth));
		bounds.reduce(boarderSize, boarderSize);
		stepButtons[step]->setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
	}
}

void Track::openFileButtonClicked()
{
	FileChooser chooser("Select a Wave or mp3 file to play...", File::nonexistent, "*.wav;*.mp3");
	if (chooser.browseForFileToOpen()) 
	{
		File file(chooser.getResult());
		AudioFormatReader *reader = formatManager.createReaderFor(file);

		if (reader != nullptr) 
		{
			ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource(reader, true);
			readerSource = newSource.release();
			transportSource.setSource(readerSource, 0, nullptr, reader->sampleRate);
			openFileButton.setButtonText(file.getFileName());
		}
		else
		{
			openFileButton.setButtonText("Open");
		}
	}
}
	
void Track::sliderValueChanged(Slider * slider)
{
	if (slider == &trackLevelSlider)
	{
		trackLevel = slider->getValue();
	}
}

void Track::buttonClicked(Button * button)
{
	if (button == &openFileButton)
	{
		Logger::outputDebugString("OPEN BUTTON PRESSED!!");
		openFileButtonClicked();
	}
}

void Track::nextStep()
{
	stepButtons[(currentStepIndex + numSteps - 1) % numSteps]->toggleCurrent(false);
	stepButtons[currentStepIndex]->toggleCurrent(true);
	if (stepButtons[currentStepIndex]->getToggleState())
	{
		transportSource.setPosition(0);
		transportSource.start();
	}
	currentStepIndex++;
	currentStepIndex %= numSteps;
}

// AudioSource Inherited Functions
void Track::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void Track::releaseResources()
{
	transportSource.releaseResources();
}

void Track::getNextAudioBlock(const AudioSourceChannelInfo & bufferToFill)
{
	transportSource.getNextAudioBlock(bufferToFill);
	bufferToFill.buffer->applyGain(trackLevel);
}
