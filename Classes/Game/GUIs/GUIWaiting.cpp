#include "GUIWaiting.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../GUIManager.h"
GUIWaiting::GUIWaiting(void) : BaseGUI()
{
	BaseGUI();
}


GUIWaiting::~GUIWaiting(void)
{
}

void GUIWaiting::initGUI(){
    BaseGUI::initGUI();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	GameImage* background = addImage("bgDark.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);

	loading = this->addImage("iconLoading.png");
	loading->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 359)));
	loading->setPosition(size.width * 0.5f, size.height * 0.5f);
}


void GUIWaiting::callbackCompleteEndGame()
{
	
}

void GUIWaiting::showGUI( CCNode* parent /* = NULL */, bool hasFog /* = true */ )
{
	BaseGUI::showGUI();
	loading->cleanup();
	loading->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 359)));
}
