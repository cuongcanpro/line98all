#ifndef GUIMenuBomb_H
#define GUIMenuBomb_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
#include "dragonbones/DragonBones.h"
#include "dragonbones/renderer/DBCCFactory.h"
using namespace cocos2d::ui;
using namespace dragonBones;
class GUIMenuBomb : public BaseGUI
{
private:
	Scale9Sprite* bg;
	BaseButton* arrayButton[4];
	BaseButton* btnClose, *btnNewGame;
	Text* arrayLabel[4];
public:
	int currentLevel;
public:
	void initGUI();
	void onButtonRelease(int buttonId, CCTouch* event);
	void hideGUI();
	void showGUI();
	void moveEffect(Node* node, int rate, float delay = 0);
	void loadSound();
	void updateCurrentLevel(int currentLevel);
};
#endif