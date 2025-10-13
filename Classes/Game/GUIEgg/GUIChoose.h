#pragma once
#ifndef GUIChoose_h__
#define GUIChoose_h__
#include "../../Engine/GUI/BaseGUI.h"
class GUIChoose : public BaseGUI
{
public:
	GUIChoose(void);
	~GUIChoose(void);

	GameImage* leftWall, *rightWall, *upWall;
	LabelBM* labelEndless, *labelStomp, *labelTime, *labelLine, *labelTwenty, *labelMerge, *labelGame;
	BaseButton* btnEndless;
	BaseButton* btnStomp;
	BaseButton* btnTime;
	BaseButton* btnBack;
	BaseButton* btnSound;
	BaseButton* btnLines;
	BaseButton* btnTwenty;
	BaseButton* btnMerge;
	BaseButton* btnVibrate;
	BaseButton* btnGame;

	void onBackKey(void);
	void callBackSplash();
	void initGUI();
    void showGUI(CCNode* parent = NULL, bool hasFog = true);
	void onButtonRelease(int buttonID, CCTouch* touch);
	void loadVibrate();
};
#endif // GUIChoose_h__

