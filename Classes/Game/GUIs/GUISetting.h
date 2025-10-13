#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"

using namespace std;


class GUISetting : public BaseGUI
{
public:
	GUISetting(void);
	~GUISetting(void);
	void initGUI();
	BaseButton* arrayButton[6];
	BaseButton* arrayBall[9];
	GameImage* arraySignal[9];
	BaseButton* btnAnimation;
	GameImage* iconSelectAnimation;
	GameImage* iconSelect;
	GameImage* bgSelect;
	extension::ControlSlider* slider;
	float sizeBall;
	float startBallX;
	vector <int> arrayIdSelect;
	vector <int> arrayIdUnSelect;

	GameImage* iconSelectLanguage;
	BaseButton* arrayBtnLanguage[4];
	GameImage* arrayIconLanguage[4];
	Label* labelLanguage;

	void onButtonRelease(int buttonID, CCTouch* touch);
	void update();
    void callBackSplash();
	void onBackKey();
	void updateIconSelect();
	void showGUI(CCNode* parent, bool hasFog);
	void updateCurrentBall();
	void updateSizeBall(float dt);
	Label* label, *label1, *label2, *label3, *label4, *label5, *label6;
	void updateLocalize();
};

