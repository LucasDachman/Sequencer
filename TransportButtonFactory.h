/*
  ==============================================================================

    TransportButtonFactory.h
    Created: 25 Oct 2017 6:21:39pm
    Author:  Lucas

  ==============================================================================
*/

/* 
	A ToolbarItemFactory. The factory creates items of type ToolbarItemComponent.
	In this case we can use a ToolbarButton. ToolbarButtons will be added to the
	Toolbar which acts as a transport panel.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TransportButtonFactory : public ToolbarItemFactory
{
public:
	// Inherited via ToolbarItemFactory
	virtual void getAllToolbarItemIds(Array<int>& ids) override;
	virtual void getDefaultItemSet(Array<int>& ids) override;
	virtual ToolbarItemComponent * createItem(int itemId) override;

private:
	// private members
	Array<int> currentIds;
	
	// private functions
	ToolbarItemComponent * createPlayButton(int itemId);

};
