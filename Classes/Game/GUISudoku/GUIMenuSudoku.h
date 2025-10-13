#ifndef GUIMenuSudoku_H
#define GUIMenuSudoku_H

#include "../../Engine/GUI/BaseGUI.h"
#include "ui/UIText.h"
using namespace cocos2d::ui;
class GUIMenuSudoku : public BaseGUI
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
	void onButtonRelease(int buttonId, Touch* event);
	void hideGUI();
	void showGUI();
	void moveEffect(Node* node, int rate, float delay = 0);
	void loadSound();
	void updateCurrentLevel(int currentLevel);
};
#endif
