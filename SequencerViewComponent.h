/*
==============================================================================
Author: Lucas Dachman
Date: 10/12/17
==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Track.h"
#include "TransportComponent.h"

class SequencerViewComponent : public AudioAppComponent,
	public Timer
{
public:
	//==============================================================================
	SequencerViewComponent()
		: transportComponent(&transportController)
	{
		// specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);

		//set bpm
		BPM = 120;

		// Create Track objs, make visible and add to array
		for (int track = 0; track < NUM_TRACKS; track++)
		{
			tracksArray.add(new Track(NUM_STEPS));
			addAndMakeVisible(tracksArray.getLast());
		}

		// Transport Toolbar
		addAndMakeVisible(transportComponent);
		transportController.setBPM(BPM);
		transportController.setTracks(&tracksArray);

		// Set the Window Size
		//setSize(800, 500);

		Timer::startTimer(10);
		transportController.startTransport();
	}

	~SequencerViewComponent()
	{
		shutdownAudio();
	}

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
	{
		transportController.prepareToPlay(samplesPerBlockExpected, sampleRate);
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		transportController.getNextAudioBlock(bufferToFill);
	}

	void timerCallback() override
	{
		repaint();
	}

	void releaseResources() override
	{
		// This will be called when the audio device stops, or when it is being
		// restarted due to a setting change.

		//mixerAudioSrc.removeAllInputs();
		transportController.releaseResources();
	}

	//==============================================================================
	void paint(Graphics& g) override
	{
		g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	}

	void resized() override
	{
		auto r = getLocalBounds();
		auto topSection = r.removeFromTop(50);

		transportComponent.setBounds(topSection);

		int trackHeight = r.getHeight() / NUM_TRACKS;
		for (int track = 0; track < tracksArray.size(); track++)
		{
			tracksArray[track]->setBounds(r.getX(), r.getY() + trackHeight*track, r.getWidth(), trackHeight);
		}
	}

	void handleMidiMessage(MidiMessage m)
	{
		int area = 16;
		int col = m.getNoteNumber() % area;
		int row = m.getNoteNumber() / area;
        if (col < NUM_STEPS && row < NUM_TRACKS)
		    tracksArray[row]->stepButtons[col]->setToggleState(m.isNoteOn(), true);
	}

private:
	//==============================================================================
	const int NUM_STEPS = 4;
	const int NUM_TRACKS = 4;

	OwnedArray<Track> tracksArray;
	//MixerAudioSource mixerAudioSrc;
	TransportComponent transportComponent;
	TransportController transportController;
	int BPM;

//	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
//Component* createMainContentComponent() { return new MainContentComponent(); }
