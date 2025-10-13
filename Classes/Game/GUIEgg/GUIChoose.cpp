#include "GUIChoose.h"
#include "Game/Utility/GameSound.h"
#include "Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "Engine/GUI/ParticleEffect.h"
#include "../Utility/JNIUtils.h"
#include "Game/Utility/GameUtility.h"

#define BTN_BACK 1
#define BTN_SOUND 2
#define BTN_STOMP 3
#define BTN_TIME 4
#define BTN_END 5
#define BTN_LINES 6
#define BTN_TWENTY 7
#define BTN_MERGE 8
#define BTN_VIBRATE 9
#define BTN_GAME 10

GUIChoose::GUIChoose(void)
{
	setKeypadEnabled(true);
}


GUIChoose::~GUIChoose(void)
{
}

void GUIChoose::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    callBackSplash();
	//runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFunc::create(this, callfunc_selector(GUIChoose::callBackSplash)), NULL));
}

void GUIChoose::onBackKey(void)
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this) {
		game->endGame();
	}
}

void GUIChoose::callBackSplash()
{
	BaseGUI::initGUI();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("egg/jungleback.jpg");
	background->setAnchorPoint(ccp(0, 0));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	leftWall = addImage("egg/leftwall.png");
	leftWall->setHeight(size.height);
	leftWall->setPositionX(leftWall->getRealWidth() * 0.5f);
	leftWall->setPositionY(size.height * 0.5f);

	rightWall = addImage("egg/rightwall.png");
	rightWall->setHeight(size.height);
	rightWall->setPosition(size.width - rightWall->getRealWidth() * 0.5f, 0);
	rightWall->setPositionY(size.height * 0.5f);

	upWall = addImage("egg/upwall.png");
	upWall->setWidth(size.width);
	upWall->setPosition(size.width * 0.5f, size.height - upWall->getRealHeight() * 0.1f);

	btnBack = addButton(BTN_BACK, "egg/btnBack.png");
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, upWall->getPositionY() - upWall->getRealHeight() * 0.4f + btnBack->getHeight() * 0.5f);

	btnSound = addButton(BTN_SOUND, "egg/btnSoundOff.png");
	btnSound->setPosition(btnBack->getPositionX() - btnSound->getWidth() * 1.2f, btnBack->getPositionY());

	if(game->music)
	{
		btnSound->normalImage->setImage("egg/btnSoundOn.png");
	}
	else
	{
		btnSound->normalImage->setImage("egg/btnSoundOff.png");
	}

	btnVibrate = addButton(BTN_VIBRATE, "egg/btnSoundOff.png");
	btnVibrate->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.2f, btnBack->getPositionY());
	loadVibrate();

	float pad = 1.95f;
	if (size.width / size.height >= 2.0f / 3.0f) {
		//pad = 1.55f;
	}

	btnEndless = addButton(BTN_END, "egg/endless.png");
	btnEndless->setPosition(size.width * 0.5f, upWall->getPositionY() - upWall->getHeight() * 0.6f - btnEndless->getHeight() * 0.5f);

	btnStomp = addButton(BTN_STOMP, "egg/stomp.png");
	btnStomp->setPosition(size.width * 0.5f, btnEndless->getPositionY() - btnEndless->getHeight() * pad);

	btnTime = addButton(BTN_TIME, "egg/timetrial.png");
	btnTime->setPosition(size.width * 0.5f, btnStomp->getPositionY() - btnEndless->getHeight() * pad);

	btnGame = addButton(BTN_GAME, "egg/iconPuzzel.png");
	btnGame->setPosition(size.width * 0.5f, btnTime->getPositionY() - btnEndless->getHeight() * pad);

	labelEndless = LabelBM::create("Endless Mode", FONT_BOLD_TYPE);
	addChild(labelEndless);
	labelEndless->setPosition(size.width * 0.5f, btnEndless->getPositionY() - btnEndless->getHeight() * 0.8f);

	labelStomp = LabelBM::create("Stomp Mode", FONT_BOLD_TYPE);
	addChild(labelStomp);
	labelStomp->setPosition(size.width * 0.5f, btnStomp->getPositionY() - btnEndless->getHeight() * 0.8f);

	labelTime = LabelBM::create("Timerial Mode", FONT_BOLD_TYPE);
	addChild(labelTime);
	labelTime->setPosition(size.width * 0.5f, btnTime->getPositionY() - btnEndless->getHeight() * 0.8f);

	labelGame = LabelBM::create("Puzzel Game", FONT_BOLD_TYPE);
	addChild(labelGame);
	labelGame->setPosition(size.width * 0.5f, btnGame->getPositionY() - btnGame->getHeight() * 0.8f);

	Layer *layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
	string s = "particles/leaf.plist";
	//	s = "particles/vip.plist";

	ParticleEffect *effect = new ParticleEffect();
	effect->create(s.c_str(), layer);
	effect->particle->setPosition(size.width * 0.5f, size.height);
	effect->particle->setBlendAdditive(false);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/fire_work/skeleton.xml", "fire_work");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/fire_work/texture.plist", "fire_work");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/LightBg/skeleton.xml", "LightBg");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/LightBg/texture.plist", "LightBg");
	DBCCArmatureNode* effectLight = DBCCFactory::getInstance()->buildArmatureNode("LightBg");
	effectLight->getAnimation()->gotoAndPlay("1");
	this->addChild(effectLight);
	effectLight->setPosition(size.width * 0.5, size.height * 0.7);
	effectLight->setScale(2.5);
	effectLight->setOpacity(170);

	// 	effect =  effectMgr->addParticleEffect("particles/egg.plist", ccp (px, py), layer);
	// 	effect->particle->setBlendAdditive(false);
	// 
//	effect = effectMgr->addParticleEffect("particles/ball.plist", ccp(px, py), layer);
//	effect->particle->setBlendAdditive(false);

}

void GUIChoose::showGUI(CCNode* parent, bool hasFog )
{
	JNIUtils::showAdsBanner(1);
    BaseGUI::showGUI(parent, hasFog);
    if(game->music && isInitted())
    {
        btnSound->normalImage->setImage("egg/btnSoundOn.png");
    }
    else
    {
        btnSound->normalImage->setImage("egg/btnSoundOff.png");
    }

	moveElement(leftWall->getImg(), 200, 0, 0);
	moveElement(rightWall->getImg(), -200, 0, 0);

	moveElement(btnGame->normalImage->getImg(), 0, -500, 0);
	moveElement(btnTime->normalImage->getImg(), 0, -500, 0.1);
	moveElement(btnStomp->normalImage->getImg(), 0, -500, 0.2);
	moveElement(btnEndless->normalImage->getImg(), 0, -500, 0.3);
	moveElement(upWall->getImg(), 0, -500, 0.4);

	labelEndless->setOpacity(0);
	labelStomp->setOpacity(0);
	labelTime->setOpacity(0);
	labelGame->setOpacity(0);

	labelGame->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.5), NULL));
	labelTime->runAction(CCSequence::create(CCDelayTime::create(0.4), CCFadeIn::create(0.5), NULL));
	labelStomp->runAction(CCSequence::create(CCDelayTime::create(0.5), CCFadeIn::create(0.5), NULL));
	labelEndless->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.5), NULL));
}

void GUIChoose::onButtonRelease( int buttonID, CCTouch* touch )
{
	GameSound::playClick();
    if (buttonID != BTN_BACK && game->isInitAds == false) {
        string packageApp = JNIUtils::getPackageApp();
        if (packageApp.compare("com.lightgames.eggShoot2017") == 0) {
            // google test
            CCLOG("INIT ADS");
            //JNIUtils::initAds("ca-app-pub-3500982632045294~9038691366", "ca-app-pub-3940256099942544/6300978111", "ca-app-pub-3940256099942544/1033173712", 1, 1);

            // my ads
           // idAdsBanner = 1;
            JNIUtils::initAds("ca-app-pub-3500982632045294~7897289512", "ca-app-pub-3500982632045294/3958044502", "ca-app-pub-3500982632045294/7182634333", idAdsBanner, idAdsBanner); // viettv
        }
        else {
            CCLOG("PACKAGE %s", packageApp.c_str());
        }
    }
	
	switch (buttonID)
	{
	case BTN_BACK:
		{

			game->endGame();
		}

		break;
	case BTN_SOUND:
		{
			
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("egg/btnSoundOn.png");
			}
			else
			{
				btnSound->normalImage->setImage("egg/btnSoundOff.png");
			}

			CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
			CCUserDefault::sharedUserDefault()->flush();

		}
		break;
	case BTN_END:
		{
		game->loadEgg();
		JNIUtils::sendEvent("choose_game_endless", "1");
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiTopEgg.showTop(TOP_NORMAL);
		return;
			
		}
		break;
	case BTN_STOMP:
		{
			game->loadEgg();
			JNIUtils::sendEvent("choose_game_stomp", "1");
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLevelEgg);

		}
		break;
	case BTN_TIME:
		{
		JNIUtils::sendEvent("choose_game_time", "1");
		game->loadEgg();
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiTopEgg.showTop(TOP_TIME);
		}
		break;
	case BTN_GAME:
	{
		JNIUtils::sendEvent("choose_game_puzzel", "1");
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
		
	}
	break;
	
	case BTN_VIBRATE:
	{
		//game->onReward(0);
		//JNIUtils::openApp("com.bcsofts.colorLines2016&referrgder=lfdjflfdjlfsj");
		game->vibrate = !game->vibrate;
		loadVibrate();

		CCUserDefault::sharedUserDefault()->setBoolForKey("vibrate", game->vibrate);
		CCUserDefault::sharedUserDefault()->flush();
	}
	break;
	default:
		break;
	}
}

void GUIChoose::loadVibrate()
{
	if (game->vibrate)
	{
		btnVibrate->normalImage->setImage("egg/btnVibrateEnable.png", false);
	}
	else
	{
		btnVibrate->normalImage->setImage("egg/btnVibrateDisable.png", false);
	}
}
