#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUIHelp : public BaseGUI
{
public:
	GUIHelp(void);
	~GUIHelp(void);
public:
	void initGUI();
private:
	

public:
	virtual void onBackKey(void);
	

	void onButtonRelease(int buttonID, CCTouch* touch);
	void update();
    void callBackSplash();

};

