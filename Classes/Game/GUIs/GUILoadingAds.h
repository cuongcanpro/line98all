#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;

class GUILoadingAds : public BaseGUI
{
public:
	GUILoadingAds(void);
	~GUILoadingAds(void);
	void initGUI();

	GameImage* loading;
	void autoHideGUI();
	void showAds(bool needLoad);
	void callbackShowAds();
	virtual void showGUI(CCNode* parent = NULL , bool hasFog = true);

};

