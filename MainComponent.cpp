/*
  ==============================================================================
  Author: Lucas Dachman
  Date: 10/12/17
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerViewComponent.h"
#include "MidiViewComponent.h"
#include "SequencerLookAndFeel.h"

class MainContentComponent   :	public TabbedComponent
{
public:
    //==============================================================================
	MainContentComponent()
		: TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop),
		midiViewComponent(&sequencerViewComponent)
    {
		setSize(800, 500);
		setLookAndFeel(&lookAndFeel);
		addTab("Sequencer View", Colours::white, &sequencerViewComponent, true);
		addTab("Midi View", lookAndFeel.PRIMARY_COLOUR, &midiViewComponent, true);
    }

private:
    //==============================================================================
	SequencerViewComponent sequencerViewComponent;
	MidiViewComponent midiViewComponent;

	SequencerLookAndFeel lookAndFeel;
	
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
