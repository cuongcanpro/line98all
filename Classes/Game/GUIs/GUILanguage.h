#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUILanguage : public BaseGUI
{
public:
	GUILanguage(void);
	~GUILanguage(void);
	void initGUI();
	BaseButton* arrayBtn[4];
	GameImage* iconLanguage[4];
	GameImage* iconSelect;
	Label* label;
	void onButtonRelease(int buttonID, CCTouch* touch);
	void update();
    void callBackSplash();
	void updateLocalize();
};

