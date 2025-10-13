#pragma once
#ifndef GUILevelEgg_h__
#define GUILevelEgg_h__
#include "../../Engine/GUI/BaseGUI.h"
#include "TableListPostureEgg.h"
class GUILevelEgg : public BaseGUI
{
public:
	GUILevelEgg(void);
	~GUILevelEgg(void);

	BaseButton* btnBack;
	BaseButton* btnSound;
	TableView* listLevel;
	void initGUI();
	void onButtonRelease(int buttonID, CCTouch* touch);
	void onBackKey(void);
	void showGUI(CCNode* parent = NULL, bool hasFog = true);
};
#endif // GUILevelEgg_h__

