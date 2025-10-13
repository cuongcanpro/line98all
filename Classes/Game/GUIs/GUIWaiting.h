#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;

class GUIWaiting : public BaseGUI
{
public:
	GUIWaiting(void);
	~GUIWaiting(void);
	void initGUI();
	void callbackCompleteEndGame();

	GameImage* loading;
	virtual void showGUI(CCNode* parent = NULL , bool hasFog = true);
};

