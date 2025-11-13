#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUITypeSudoku : public BaseGUI
{
public:
	GUITypeSudoku(void);
	~GUITypeSudoku(void);
	void initGUI();
	BaseButton* btnBack, *btnSound, *btnSetting;
	BaseButton* btnTime, *btnNormal, *btnLevel, *btnChallenge;
    BaseButton* btnUpdate, *btnGame;
	void onButtonRelease(int buttonID, Touch* touch);
    void callBackSplash();
	void onBackKey();
	void showGUI(Node* parent = NULL , bool hasFog = true);
	void updateButton();

	vector<BaseButton*> arrayButton;
};

