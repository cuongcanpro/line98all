#pragma once
#include "Engine/GUI/BaseGUI.h"
#ifndef GUIChangeNameEgg_h__
#define GUIChangeNameEgg_h__


using namespace std;
using namespace cocos2d::extension;

class GUIChangeNameEgg : public BaseGUI
{
public:
	GUIChangeNameEgg(void);
	~GUIChangeNameEgg(void);
public:
	ui::Scale9Sprite *bg;
	void initGUI();
	void showGUI(CCNode* parent = NULL, bool hasFog = true);
	ui::EditBox* nameBox;
	int currentTop;
	static std::string className;
	void onBackKey();
};
#endif // GUIChangeNameEgg_h__

