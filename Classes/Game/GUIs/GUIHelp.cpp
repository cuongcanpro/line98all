#include "GUIHelp.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Data/GlobalData.h"
#include "../Utility/GameUtility.h"
#include "Game/Data/GlobalData.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_READY_ID 1

GUIHelp::GUIHelp(void) : BaseGUI()
{
	BaseGUI();
}


GUIHelp::~GUIHelp(void)
{
}


void GUIHelp::initGUI(){

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUILoading::callBackSplash)), NULL));
	runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIHelp::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);
//    callBackSplash();

}

void GUIHelp::onBackKey(){
}



void GUIHelp::onButtonRelease(int buttonID, CCTouch* touch)
{
	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_READY_ID:
		{
			if (!GUIManager::getInstance().guiLine.isInitted() || !GUIManager::getInstance().guiLine.isVisible())
			{
				GUIManager::getInstance().removeFromListGui();
				GUIManager::getInstance().guiLine.showGuiWithMode(0);
			}
			else
			{
				GUIManager::getInstance().removeFromListGui();
			}
			
		}
		
	
	default:
		break;
	}
}

void GUIHelp::callBackSplash()
{
	BaseGUI::initGUI();
	
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	GameImage* contentHelp = addImage("help.png", 0, 0, 0, true);
	contentHelp->setPos(size.width / 2, size.height * 0.98f - contentHelp->getRealHeight() * 0.5f);

	BaseButton* btnReady = addButton(BTN_READY_ID, "btnReady.png", new BubbleBehavior(), NULL, true);
	btnReady->setPosition(size.width * 0.5f, size.height * 0.15f);

}

