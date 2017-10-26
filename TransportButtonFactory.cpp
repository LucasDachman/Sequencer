/*
  ==============================================================================

    TransportButtonFactory.cpp
    Created: 25 Oct 2017 6:21:39pm
    Author:  Lucas

  ==============================================================================
*/

#include "TransportButtonFactory.h"

void TransportButtonFactory::getAllToolbarItemIds(Array<int>& ids)
{
	ids.addArray(currentIds);
}

void TransportButtonFactory::getDefaultItemSet(Array<int>& ids)
{
	ids.addArray(currentIds);
}

ToolbarItemComponent * TransportButtonFactory::createItem(int itemId)
{
	currentIds.add(itemId);
	return createPlayButton(itemId);
}

ToolbarItemComponent * TransportButtonFactory::createPlayButton(int itemId)
{
	DrawableText * normalImage = new DrawableText();
	DrawableText * toggledOnImage = new DrawableText();
	normalImage->setText("Play");
	normalImage->setColour(Colours::grey);
	toggledOnImage->setText("Stop");
	toggledOnImage->setColour(Colours::blue);
	ToolbarButton * newButton =
		new ToolbarButton(itemId, "Play", normalImage, toggledOnImage);
	newButton->setClickingTogglesState(true);
	return newButton;
}
