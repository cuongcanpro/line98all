#include "GUILoadingGame.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3


GUILoadingGame::GUILoadingGame(void) : BaseGUI()
{
	BaseGUI();
	CCNode::onEnter();
	setKeypadEnabled(true);
}


GUILoadingGame::~GUILoadingGame(void)
{
}

void GUILoadingGame::initGUI(){
	//JNIUtils::loadOldPreferences();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(BACKGROUND_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull(PROGRESS_RES).c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
// 	CCTextureCache::sharedTextureCache()->addImage(ScreenUtils::fileFull("loading/LG2.png").c_str());
	//Image *bg1 = addImage("loading/LG2.png");
	//bg1->setWidth(size.width);
	//bg1->setHeight(size.height);
	//bg1->getImg()->runAction(CCSequence::create(CCFadeIn::create(0.8f), CCDelayTime::create(.8f), CCFadeOut::create(0.8f), CCCallFunc::create(this, callfunc_selector(GUILoadingGame::callBackSplash)), NULL));
	runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUILoadingGame::callBackSplash)), NULL));
	//bg1->setPos(size.width / 2, size.height / 2);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/iconBottom/skeleton.xml", "iconBottom");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/iconBottom/texture.plist", "iconBottom");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/iconTop/skeleton.xml", "iconTop");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/iconTop/texture.plist", "iconTop");
	Ball* ball = new Ball();
	ball->setId(3);
	addChild(ball);
	ball->setPosition(Vec2(333, 333));
}


void GUILoadingGame::callbackCompleteEndGame()
{
    JNIUtils::showTracking();
	if (updateGame == 1 || updateGame == 2)
		return;
   
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		
}

void GUILoadingGame::callBackSplash()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    GameImage* background = addImage("egg/jungleback.jpg");
    background->setWidth(size.width);
    background->setHeight(size.height);
    background->setPos(size.width / 2, size.height / 2);

	DBCCArmatureNode* eff = DBCCFactory::getInstance()->buildArmatureNode("iconBottom");
	if (eff)
	{
		eff->setScale(0.0);
		this->addChild(eff);
		eff->setPosition(size.width * 0.5, size.height * 0.5);
		eff->gotoAndPlay("1", -1, -1, -1);
		eff->setVisible(true);
		eff->runAction(
			Sequence::create(
				ScaleTo::create(0.3, 3),
				DelayTime::create(1.5),
				FadeOut::create(0.5),
				NULL
			)
		);

		/*effIcon->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});*/
	}
	
	Sprite* iconBall = Sprite::create("480_800/iconEggShoot.png");
	addChild(iconBall);
    iconBall->setPosition(Vec2(size.width * 0.5, size.height));
//	background->setWidth(size.width);
	//background->setHeight(size.height);
	 iconBall->runAction(
        Sequence::create(
            EaseBounceOut::create(MoveTo::create(0.8, Vec2(size.width * 0.5, size.height * 0.5))),
            DelayTime::create(0.8),
            FadeOut::create(0.5),
            CallFunc::create(this, callfunc_selector(GUILoadingGame::callbackCompleteEndGame)),
            NULL
        )
    );
    iconBall->runAction(
        Sequence::create(
            DelayTime::create(0.4),
            ScaleTo::create(0.2, 1.2, 0.65),
            EaseBounceOut::create(ScaleTo::create(0.4, 1.0, 1.0)),
                    
            NULL
        )
    );

	DBCCArmatureNode* effTop = DBCCFactory::getInstance()->buildArmatureNode("iconTop");
	if (effTop)
	{
		this->addChild(effTop);
		effTop->setPosition(size.width * 0.5, size.height * 0.5);
		effTop->gotoAndPlay("1", -1, -1, -1);
		effTop->setVisible(true);
		effTop->setScale(3);
		effTop->runAction(
			Sequence::create(
				DelayTime::create(1.5),
				FadeOut::create(0.5),
				NULL
			)
		);
		/*effIcon->setCompleteListener([](dragonBones::DBCCArmatureNode* armature) {
			armature->setVisible(false);
		});*/
	}
	GameSound::playLevelUp();
}
