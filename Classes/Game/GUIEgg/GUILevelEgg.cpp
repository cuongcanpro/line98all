#include "GUILevelEgg.h"
#include "Game/Utility/GameSound.h"
#include "Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"

#define BTN_BACK 1
#define BTN_SOUND 2
#define BTN_STOMP 3
#define BTN_TIME 4
#define BTN_END 5
GUILevelEgg::GUILevelEgg(void)
{
	setKeypadEnabled(true);
}


GUILevelEgg::~GUILevelEgg(void)
{
}

void GUILevelEgg::initGUI(){
	BaseGUI::initGUI();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("egg/jungleback.jpg");
	background->setAnchorPoint(ccp(0, 0));
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	

	GameImage* leftWall = addImage("egg/leftwall.png");
	leftWall->setHeight(size.height);
	leftWall->setPositionX(leftWall->getRealWidth() * 0.5f);
	leftWall->setPositionY(size.height * 0.5f);

	GameImage* rightWall = addImage("egg/rightwall.png");
	rightWall->setHeight(size.height);
	rightWall->setPosition(size.width - rightWall->getRealWidth() * 0.5f, 0);
	rightWall->setPositionY(size.height * 0.5f);


	GameImage* upWall = addImage("egg/upwall.png");
	upWall->setWidth(size.width);
	upWall->setPosition(size.width * 0.5f, size.height - upWall->getRealHeight() * 0.5f);

	GameImage* bgLobby = addImage("egg/bgDark.png");

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

    leftWall->setVisible(false);
    rightWall->setVisible(false);

	float heightTable = upWall->getPositionY() - upWall->getHeight() * 0.8f - size.height * 0.15f;
	bgLobby->setWidth(size.width * 0.9f);
	bgLobby->setHeight(heightTable * 1.1f);
	bgLobby->setPos(size.width * 0.5f, size.height * 0.15f - heightTable * 0.05f + bgLobby->getRealHeight() * 0.5f);

    TableListPostureEgg* tableListPosture = new TableListPostureEgg();
	listLevel = TableView::create(tableListPosture, CCSizeMake(size.width * 0.8f, heightTable));
	listLevel->setDirection(TableView::Direction::VERTICAL);
	listLevel->setAnchorPoint(ccp(0.5f, 0.5f));
	listLevel->setContentOffset(ccp(0,0));
	listLevel->setPosition(ccp(size.width * 0.1f, size.height * 0.15f));
	listLevel->setDelegate(tableListPosture);
	listLevel->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(listLevel, 3);
}

void GUILevelEgg::onButtonRelease( int buttonID, CCTouch* touch )
{
	GameSound::playClick();
	switch (buttonID)
	{
	case BTN_BACK:
		{
		onBackKey();
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
	
	default:
		break;
	}
}

void GUILevelEgg::onBackKey(void)
{
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this) {
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChoose);
		GUIManager::getInstance().isCallBackPress = true;
	}
}

void GUILevelEgg::showGUI(CCNode* parent, bool hasFog)
{
	JNIUtils::showAdsBanner(1);
	BaseGUI::showGUI(parent, hasFog);
	listLevel->reloadData();
}
