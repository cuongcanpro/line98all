#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "Entity/MiniBoard.h"

using namespace std;


class GUISave : public BaseGUI
{
public:
	GUISave(void);
	~GUISave(void);
	void initGUI();
	BaseButton* arrayBtnSave[6];
	BaseButton* arrayBtnUnSave[6];
	BaseButton* arrayBtnPlay[6];
	MiniBoard* miniBoard[6];
	LabelBM* arrayLbScore[6];
	Label* lbContent;
	GameImage* iconSelect;
	int currentIndex;
	void onButtonRelease(int buttonID, CCTouch* touch);
	void update();
    void callBackSplash();
	void onBackKey();
	//void showGUI(CCNode* parent, bool hasFog);
	void showGUI(bool isSave);
};

