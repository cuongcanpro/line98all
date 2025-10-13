#include "GUISetting.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"
#include "Game/Utility/Toast.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_SETTING_OK 10
#define BTN_ANIMATION 11



GUISetting::GUISetting(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUISetting::~GUISetting(void)
{
}


void GUISetting::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUILoading::callBackSplash)), NULL));
//	runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUILoading::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
    callBackSplash();

}

void GUISetting::callBackSplash()
{
	BaseGUI::initGUI();

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);


	label = Label::createWithTTF(CCLocalizedString("CHOOSE_TYPE_BALL").c_str(), "fonts/tahomabd.ttf", 20);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setWidth(size.width * 0.9);
	label->setPosition(size.width * 0.5, size.height * 0.97);
	if (size.width / size.height < 11.0 / 20.0) {
		label->setPosition(size.width * 0.5, size.height * 0.92);
	}
	else {
		label->setPosition(size.width * 0.5, size.height * 0.97);
	}
	this->addChild(label);

	GameImage*bgBall = addImage("bgBall.png", 0, 0, 0, true);
	bgBall->setPosition(size.width * 0.5, label->getPositionY() - 70);
	bgBall->setWidth(size.width * 0.95);

	float sum = 0;
	for (int i = 0; i < 6; i++) {
		arrayButton[i] = addButton(i, ("btnBall_" + GameUtility::toString(i) + ".png").c_str(), new BubbleBehavior(), NULL, true);
		sum = sum + arrayButton[i]->getWidth();
	//	arrayButton[i]->setPosition(arrayButton[i]->getWidth() * i * 1.5, startY);
	}
	float pad =( size.width * 0.95 - sum) / 7;
	for (int i = 0; i < 6; i++) {
		arrayButton[i]->setPosition(arrayButton[i]->getWidth() * (i + 0.5) + pad * (i + 1), bgBall->getPositionY());
	}
	for (int i = 0; i < 9; i++) {
		if (i < 7) {
			arrayIdSelect.push_back(game->arrayBall[i]);
		}
		else {
			arrayIdUnSelect.push_back(game->arrayBall[i]);
		}
	}

	label2 = Label::createWithTTF(CCLocalizedString("CHOOSE_COLOR_BALL"), "fonts/tahomabd.ttf", 20);
	label2->setHorizontalAlignment(TextHAlignment::CENTER);
	label2->setWidth(size.width * 1.0);
	label2->setPosition(size.width * 0.5, arrayButton[0]->getPositionY() - 80);
	this->addChild(label2);

	bgSelect = addImage("bgSelect.png", 0, 0, 0, true);
	float scale = size.width / bgSelect->getWidth();
	bgSelect->setScale(scale);
	bgSelect->setPosition(size.width * 0.14 + bgSelect->getRealWidth() * 0.5, label2->getPositionY() - 10 - bgSelect->getRealHeight() * 0.6);
	bgSelect->setPosition(size.width * 0.5, label2->getPositionY() - 10 - bgSelect->getRealHeight() * 0.6);

	label3 = Label::createWithTTF(CCLocalizedString("BOARD"), "fonts/tahomabd.ttf", 20);
	label3->setAnchorPoint(ccp(0, 0.5));
	label3->setWidth(size.width * 1.2);
	label3->setPosition(size.width * 0.02, bgSelect->getPositionY() + bgSelect->getRealHeight() * 0.26);
	this->addChild(label3);

	label4 =  Label::createWithTTF(CCLocalizedString("STORE"), "fonts/tahomabd.ttf", 20);
	label4->setHorizontalAlignment(TextHAlignment::LEFT);
	label4->setAnchorPoint(ccp(0, 0.5));
	label4->setWidth(size.width * 1.2);
	label4->setPosition(size.width * 0.02, bgSelect->getPositionY() - bgSelect->getRealHeight() * 0.26);
	this->addChild(label4);

	sizeBall = bgSelect->getRealWidth() * 0.85 / 7;
	startBallX = bgSelect->getPositionX() - bgSelect->getRealWidth() * 0.5 + bgSelect->getRealWidth() * 0.145;

	for (int i = 0; i < 9; i++) {
		arrayBall[i] = addButton(20 + i, "lineBall_0_0.png", NULL, NULL, false);
		float scale = sizeBall / arrayBall[i]->getWidth() * 0.8;
		arrayBall[i]->normalImage->setScale(scale);
		//arrayBall[i][j]->setPosition(arrayButton[i]->getPositionX() + arrayButton[i]->getWidth() * 0.9 + sizeBall * (j + 0.5), arrayButton[i]->getPositionY());

		
		arraySignal[i] = new GameImage("iconPlus.png", true);
		scale = sizeBall * 0.3 / arraySignal[i]->getWidth();
		arraySignal[i]->setScale(scale);
		//arrayBall[i]->normalImage->addChild(arraySignal[i]);
		arraySignal[i]->setPosition(arrayBall[i]->getPositionX() + arrayBall[i]->getWidth() * 0.4, arrayBall[i]->getPositionY() + arrayBall[i]->getHeight() * 0.4);
		this->addImage(arraySignal[i], 0);
		arraySignal[i]->setLocalZOrder(10);
	}

	updateCurrentBall();

	label5 = Label::createWithTTF(CCLocalizedString("RESIZE_BALL"), "fonts/tahomabd.ttf", 20);
	label5->setHorizontalAlignment(TextHAlignment::CENTER);
	label5->setAnchorPoint(ccp(0.5, 0.5));
	label5->setWidth(size.width * 1.2);
	label5->setPosition(size.width * 0.5, bgSelect->getPositionY() - bgSelect->getRealHeight() * 0.8);
	this->addChild(label5);

	slider = extension::ControlSlider::create("bgProgressEvent.png", "progressEvent.png", "dot.png");
	//slider->setScale(0.5);
	addChild(slider);
	slider->setPosition(size.width * 0.5, label5->getPositionY() - 30);
	slider->setMinimumValue(0.6);
	slider->setMaximumValue(0.9);
	slider->setValue(game->scaleBall);

	iconSelect = addImage("iconSelect.png", 0, 0, 0, true);
	updateIconSelect();

	btnAnimation = addButton(BTN_ANIMATION, "noSelect.png", new BubbleBehavior(), NULL, true);
	btnAnimation->setPosition(size.width * 0.2, slider->getPositionY() - 50);
	btnAnimation->normalImage->setScale(1.3);

	iconSelectAnimation = addImage("iconAutoSelect.png", 0, 0, 0, true);
//	iconSelectAnimation->removeTouch();
	//iconSelectAnimation->setScale(3);
	iconSelectAnimation->setPosition(btnAnimation->getPosition());
	iconSelectAnimation->setLocalZOrder(10);
	//iconSelectAnimation->setPosition(200, 200);

	label1 = Label::createWithTTF(CCLocalizedString("SHOW_ANIMATION"), "fonts/tahomabd.ttf", 20);
	label1->setAnchorPoint(ccp(0, 0.5));
	label1->setWidth(size.width * 1.2);
	label1->setPosition(btnAnimation->getPositionX() + 30, btnAnimation->getPositionY() - 5);
	this->addChild(label1);

	labelLanguage = Label::createWithTTF(CCLocalizedString("CHOOSE_LANGUAGE").c_str(), "fonts/tahomabd.ttf", 20);
	labelLanguage->setHorizontalAlignment(TextHAlignment::CENTER);
	labelLanguage->setWidth(size.width * 0.9);
	//	label->setScale(0.8);
	this->addChild(labelLanguage);
	labelLanguage->setPosition(size.width * 0.5, btnAnimation->getPositionY() - btnAnimation->getHeight() * 1.1);
	//labelLanguage->setVisible(false);

	for (int i = 0; i < 4; i++) {
		arrayBtnLanguage[i] = addButton(40 + i, ("flag_" + GameUtility::toString(i) + ".png").c_str(), new BubbleBehavior(), NULL, false);
		//arrayIconLanguage[i] = addImage(("flag_" + GameUtility::toString(i) + ".png").c_str(), 0, 0, 0, false);
		arrayBtnLanguage[i]->setPosition(size.width * 0.5 - 120 * 1.5 + 120 * (i), label1->getPositionY() - 20 - arrayBtnLanguage[i]->getHeight() * 1.5);
		//arrayIconLanguage[i]->setPosition(arrayBtnLanguage[i]->getPositionX() + arrayBtnLanguage[i]->getWidth() * 1.2, arrayBtnLanguage[i]->getPositionY());
	}

	iconSelectLanguage = addImage("iconCircle.png", 0, 0, 0, false);
	iconSelectLanguage->setPosition(arrayBtnLanguage[language]->getPosition());


	BaseButton* btn = addButton(BTN_SETTING_OK, "btnOk.png", new BubbleBehavior(), NULL, true);
	btn->setPosition(size.width * 0.5, iconSelectLanguage->getPositionY() - btn->getHeight() * 1.2);

	
}

void GUISetting::updateSizeBall(float dt) {
	//CCLOG("value %f", slider->getValue());
	game->scaleBall = slider->getValue();
	for (int i = 0; i < 9; i++) {
		float scale = sizeBall * game->scaleBall / arrayBall[i]->getWidth();
		arrayBall[i]->normalImage->setScale(scale);
	}
}

void GUISetting::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().isCallBackPress = true;
		GUIManager::getInstance().removeFromListGui();
	}
}

void GUISetting::updateIconSelect() {
	iconSelect->setPosition(this->arrayButton[game->typeBall]->getPosition());
}

void GUISetting::showGUI(CCNode * parent, bool hasFog)
{
	BaseGUI::showGUI(parent, hasFog);
	updateIconSelect();
	iconSelectAnimation->setVisible(game->showAnimation);
	schedule(CC_SCHEDULE_SELECTOR(GUISetting::updateSizeBall), 0.02f);
}

void GUISetting::updateCurrentBall()
{
	int count = 0;
	float startY = arrayButton[0]->getPositionY() - 100;
	for (int i = 0; i < arrayIdSelect.size(); i++) {
		startY = bgSelect->getPositionY() + bgSelect->getRealHeight() * 0.26;
		arrayBall[i]->normalImage->setImage(("lineBall_" + GameUtility::toString(game->typeBall) + "_" + GameUtility::toString(arrayIdSelect.at(i)) + ".png").c_str(), false);
		arrayBall[i]->setPosition(startBallX + sizeBall * (i + 0.5), startY);
		arraySignal[i]->setImage("iconMinus.png", true);
		arraySignal[i]->setPosition(arrayBall[i]->getPositionX() + sizeBall * 0.4, arrayBall[i]->getPositionY() + sizeBall * 0.4);
		count++;
	}

	for (int i = 0; i < arrayIdUnSelect.size(); i++) {
		startY = bgSelect->getPositionY() - bgSelect->getRealHeight() * 0.26;
		arrayBall[count]->normalImage->setImage(("lineBall_" + GameUtility::toString(game->typeBall) + "_" + GameUtility::toString(arrayIdUnSelect.at(i)) + ".png").c_str(), false);
		arrayBall[count]->setPosition(startBallX + sizeBall * (i + 0.5), startY);
		arraySignal[count]->setImage("iconPlus.png", true);
		arraySignal[count]->setPosition(arrayBall[count]->getPositionX() + sizeBall * 0.4, arrayBall[count]->getPositionY() + sizeBall * 0.4);
		count++;
	}
}


void GUISetting::updateLocalize() {
	label1->setString(CCLocalizedString("SHOW_ANIMATION"));
	label2->setString(CCLocalizedString("CHOOSE_COLOR_BALL"));
	label3->setString(CCLocalizedString("BOARD"));
	label4->setString(CCLocalizedString("STORE"));
	label5->setString(CCLocalizedString("RESIZE_BALL"));
	//label6->setString(CCLocalizedString("SHOW_ANIMATION"));
	label->setString(CCLocalizedString("CHOOSE_TYPE_BALL"));
	labelLanguage->setString(CCLocalizedString("CHOOSE_LANGUAGE"));
}

void GUISetting::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
		GameSound::playClick();
	case BTN_SETTING_OK:
	{
		if (arrayIdSelect.size() == 7) {
			int i;
			string s = "";
			for (i = 0; i < 9; i++) {
				if (i < 7)
					game->arrayBall[i] = arrayIdSelect.at(i);
				else
					game->arrayBall[i] = arrayIdUnSelect.at(i - 7);
				if (i == 0) {
					s = s + GameUtility::toString(game->arrayBall[i]);
				}
				else {
					s = s + "," + GameUtility::toString(game->arrayBall[i]);
				}
			}

			CCUserDefault::sharedUserDefault()->setStringForKey("arrayBall", s);
			CCUserDefault::sharedUserDefault()->setFloatForKey("scaleBall", game->scaleBall);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("language", language);
			CCUserDefault::sharedUserDefault()->flush();
		}
		
		hideGUI();
	}

	break;
	case BTN_ANIMATION:
	{
		game->showAnimation = !game->showAnimation;
		iconSelectAnimation->setVisible(game->showAnimation);
		CCUserDefault::sharedUserDefault()->setBoolForKey("showAnimation2", game->showAnimation);
		CCUserDefault::sharedUserDefault()->setBoolForKey("showAnimation", game->showAnimation);
		CCUserDefault::sharedUserDefault()->flush();
		break;
	}
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	{
		game->typeBall = buttonID;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("typeBallNew", game->typeBall);
		CCUserDefault::sharedUserDefault()->flush();
		arrayIdSelect.clear();
		arrayIdUnSelect.clear();
		for (int i = 0; i < 9; i++) {
			if (i < 7) {
				arrayIdSelect.push_back(game->arrayBall[i]);
			}
			else {
				arrayIdUnSelect.push_back(game->arrayBall[i]);
			}
		}
	
		updateIconSelect();
		updateCurrentBall();
		break;
	}
	case 40:
	case 41:
	case 42:
	case 43:
	{
		int id = buttonID - 40;
		iconSelectLanguage->setPosition(arrayBtnLanguage[id]->getPosition());
		language = id;
		changeLanguage(language);
		updateLocalize();
	}
	break;
	default:
		int convert = buttonID - 20;
		if (convert <= arrayIdSelect.size() - 1) {
			if (arrayIdUnSelect.size() >= 7) {
				Toast::makeToast(4.0, CCLocalizedString("FULL_IN_STORE").c_str());
				return;
			}
			// bong da duoc chon -> remove
			int id = arrayIdSelect.at(convert);
			arrayIdSelect.erase(arrayIdSelect.begin() + convert, arrayIdSelect.begin() + convert + 1);
			arrayIdUnSelect.push_back(id);
		}
		else {
			if (arrayIdSelect.size() >= 7) {
				Toast::makeToast(4.0, CCLocalizedString("FULL_IN_BOARD").c_str());
				return;
			}
			convert = convert - arrayIdSelect.size();
			int id = arrayIdUnSelect.at(convert);
			arrayIdUnSelect.erase(arrayIdUnSelect.begin() + convert, arrayIdUnSelect.begin() + convert + 1);
			arrayIdSelect.push_back(id);
		}
		updateCurrentBall();
		break;
	}
}


