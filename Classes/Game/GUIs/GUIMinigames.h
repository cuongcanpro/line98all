#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "ui/UIButton.h"
using namespace std;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class GUIMinigames : public BaseGUI, public ScrollViewDelegate
{
public:
	GUIMinigames(void);
	~GUIMinigames(void);
	void initGUI();
	int countScroll;
    Scale9Sprite* bgGame;
    BaseButton* btnUpdate;
	BaseButton* btnBack, *btnSound, *btnBubble, *btnBlock, *btnBomb, *btnPop, *btnDrop, *btnTwenty, *btnLine;
	cocos2d::extension::ScrollView * scrollView;
    void onEnter();
	void onButtonRelease(int buttonID, CCTouch* touch);
    void callBackSplash();
	void onBackKey();
	void sendData(int mode);
	void showGUI(CCNode* parent /* = NULL */, bool hasFog /* = true */);

	void playBlock();
	void playEgg();
	void playTwenty();
	void playBubble();
	void playBomb();
	void updateButton();
	void onTouchBegan(CCObject *pSender, cocos2d::ui::TouchEventType type);
	vector<Button*> arrayButtonGame;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override;
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) override;
    bool onTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
};

