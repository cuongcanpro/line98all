#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUIHelpBlock : public BaseGUI
{
public:
	GUIHelpBlock(void);
	~GUIHelpBlock(void);
public:
	void initGUI();
private:
	

public:
	virtual void onBackKey(void);
	

	void onButtonRelease(int buttonID, CCTouch* touch);
	void update();
    void callBackSplash();

};

