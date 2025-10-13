#include "GUILanguage.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"


#define BTN_OK_ID 1


GUILanguage::GUILanguage(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUILanguage::~GUILanguage(void)
{
}


void GUILanguage::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    callBackSplash();
}

void GUILanguage::updateLocalize()
{
	label->setString(CCLocalizedString("CHOOSE_LANGUAGE").c_str());
}



void GUILanguage::onButtonRelease(int buttonID, CCTouch* touch)
{
	
	switch (buttonID)
	{
           GameSound::playClick();
	case BTN_OK_ID:
		{
		
		}
		
		break;
	
	default:
		int id = buttonID - 10;
		iconSelect->setPosition(arrayBtn[id]->getPosition());
		language = id;
		changeLanguage(language);
		updateLocalize();
		break;
	}
}

void GUILanguage::callBackSplash()
{
	BaseGUI::initGUI();
	
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

		
	label = Label::createWithTTF(CCLocalizedString("CHOOSE_LANGUAGE").c_str(), "fonts/tahomabd.ttf", 24);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setWidth(size.width * 0.9);
	//	label->setScale(0.8);
	this->addChild(label);
	label->setPosition(size.width * 0.5, size.height * 0.8);

	for (int i = 0; i < 4; i++) {
		arrayBtn[i] = addButton(10 + i, ("flag_" + GameUtility::toString(i) + ".png").c_str(), new BubbleBehavior(), NULL, false);
		arrayBtn[i]->setPosition(size.width * 0.5, label->getPositionY() - 50 - arrayBtn[i]->getHeight() * 1.5 * (i + 0.5));
	}

	iconSelect = addImage("iconCircle.png", 0, 0, 0, false);
	iconSelect->setPosition(arrayBtn[0]->getPosition());

	BaseButton* btn = addButton(BTN_OK_ID, "btnOk.png", new BubbleBehavior(), NULL, true);
	btn->setPosition(size.width * 0.5, arrayBtn[3]->getPositionY() - btn->getHeight() * 1.5);
}

