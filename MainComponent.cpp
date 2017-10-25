/*
  ==============================================================================
  Author: Lucas Dachman
  Date: 10/12/17
  ==============================================================================
*/

#include "Track.h"
#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent   : public AudioAppComponent,
	public HighResolutionTimer,
	public Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);

		//set bpm
		BPM = 120;

		// Create Track objs, make visible and add to Mixer
		for (int track = 0; track < NUM_TRACKS; track++) 
		{
			tracksArray.add(new Track(NUM_STEPS));
			addAndMakeVisible(tracksArray.getLast());
			mixerAudioSrc.addInputSource(tracksArray.getLast(), true);
		}

		// Set the Window Size
        setSize (800, 500);

		Timer::startTimer(10);
		HighResolutionTimer::startTimer(60000 / BPM);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
		mixerAudioSrc.prepareToPlay(samplesPerBlockExpected, sampleRate);
//		Timer::startTimerHz(BPM / 60.0);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		mixerAudioSrc.getNextAudioBlock(bufferToFill);
    }

	void hiResTimerCallback() override
	{
		Logger::outputDebugString("Timer Callback!!");
		for (int tracki = 0; tracki < tracksArray.size(); tracki++)
		{
			Track *currentTrack = tracksArray[tracki];
			currentTrack->nextStep();
		}
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
		mixerAudioSrc.releaseResources();
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
		auto r = getBounds();
		auto topSection = r.removeFromTop(50);
		
		int trackHeight = r.getHeight() / NUM_TRACKS;
		
		for (int track = 0; track < tracksArray.size(); track++) 
		{
			tracksArray[track]->setBounds(0, trackHeight*track, r.getWidth(), trackHeight);
		}
    }


private:
    //==============================================================================
	const int NUM_STEPS = 4;
	const int NUM_TRACKS = 4;

	OwnedArray<Track> tracksArray;
	MixerAudioSource mixerAudioSrc;
	int BPM;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
