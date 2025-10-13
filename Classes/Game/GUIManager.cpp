#include "GUIManager.h"
using namespace cocos2d;

GUIManager::GUIManager(void)
{
	GUIList = new std::vector<BaseGUI *>();
	isCallBackPress = false;
}

GUIManager::~GUIManager(void)
{}

GUIManager& GUIManager::getInstance()
{
	static GUIManager instance;
	
	return instance;
}

void GUIManager::update()
{
	
}

void GUIManager::addToListGui(BaseGUI *gui)
{
	GUIList->push_back(gui);
	if(gui->isInitted())
		gui->enableGUI();
	int size = GUIList->size() - 1;
	for(int i = 0; i< size; i++)
	{

		GUIList->at(i)->disableGUI();
	}

}


void GUIManager::removeFromListGui()
{
	if(GUIList->size() == 0)
		return;
	
	BaseGUI *gui = GUIList->at(GUIList->size() - 1);
	gui->hideGUI();
	GUIList->pop_back();
	
	if(GUIList->size() == 0)
		return;

	GUIList->at(GUIList->size() - 1)->enableGUI();
}

void GUIManager::showGui( BaseGUI *gui, CCNode *parent /*= NULL*/, bool fog /*= true*/ )
{
	addToListGui(gui);
	gui->showGUI(parent, fog);
}

void GUIManager::removeAllGui()
	{
		while (GUIList->size() > 0)
		{
			GUIList->at(GUIList->size() - 1)->hideGUI();
			GUIList->pop_back();

		}
	}

BaseGUI* GUIManager::getLastGui()
{
	if (GUIList->size() == 0)
		return NULL;
	return GUIList->at(GUIList->size() - 1);
}


void GUIManager::setVisibleWaiting( bool visible )
{
	
	
}
