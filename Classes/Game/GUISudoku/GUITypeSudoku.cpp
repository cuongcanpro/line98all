#include "GUITypeSudoku.h"
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
#define BTN_NORMAL_ID 3
#define BTN_CLASSIC_ID 4
#define BTN_TIME_ID 5
#define BTN_LEVEL_ID 6
#define BTN_CHALLENGE_ID 7

#define BTN_UPDATE 8
#define BTN_FANPAGE 9
#define BTN_HIGHSCORE      10
#define BTN_LANGUAGE_ID 11
#define BTN_GAME_ID 12

GUITypeSudoku::GUITypeSudoku(void) : BaseGUI()
{
	BaseGUI();
	setKeypadEnabled(true);
}

GUITypeSudoku::~GUITypeSudoku(void)
{
}


void GUITypeSudoku::initGUI(){
	Size size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    callBackSplash();

}

void GUITypeSudoku::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().isCallBackPress = true;
        game->endGame();
	}
}


void GUITypeSudoku::callBackSplash()
{
	BaseGUI::initGUI();
	Size size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("background.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);


	btnBack = addButton(BTN_BACK_ID, "btnBack.png", new BubbleBehavior(), NULL, false);
	if (size.width / size.height < 11.0 / 20.0) {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 1.5f);
	}
	else {
		btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);
	}

	btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png", new BubbleBehavior(), NULL, false);
	btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
	if (game->music)
	{
        btnSound->normalImage->setImage("btnSoundOn.png", false);
	}
	else
	{
        btnSound->normalImage->setImage("btnSoundOff.png", false);
	}

	btnGame = addButton(BTN_GAME_ID, "btnSoundOn.png", new BubbleBehavior(), NULL, false);
	btnGame->setPosition(btnGame->getWidth() * 0.7f, btnBack->getPositionY());

	auto *label = ui::Text::create(CCLocalizedString("CHOOSE_TYPE").c_str(), "fonts/tahomabd.ttf", 24);
	label->setTextHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(size.width * 0.5, size.height * 0.9));
	//label->setWidth(size.width * 0.8);
	//	label->setScale(0.8);
	this->addChild(label);
    label->setVisible(false);

    btnUpdate = addButton(BTN_UPDATE, "btnUpdate.png", new BubbleBehavior(), NULL, false);
    btnUpdate->setPosition(btnUpdate->getWidth() * 0.6, btnBack->getPositionY());
    btnUpdate->setVisible(false);

	btnNormal = addButton(BTN_NORMAL_ID, "sudoku/btnNormal.png", new BubbleBehavior(), NULL, false);
    btnNormal->setPosition(size.width * 0.5, size.height * 0.7);
	//label->setPosition(size.width * 0.5f, btnNormal->getPositionY() + btnNormal->getHeight() * 1.0f);

	btnLevel = addButton(BTN_CHALLENGE_ID, "sudoku/btnLevel.png", new BubbleBehavior(), NULL, false);
    btnLevel->setPosition(btnNormal->getPositionX(), btnNormal->getPositionY() - btnLevel->getHeight() * 1.5f);

    arrayButton.push_back(btnNormal);
    arrayButton.push_back(btnLevel);

    btnUpdate->setVisible(updateGame >= 3);
}

void okFollow() {
    JNIUtils::openUrl("fb://facewebmodal/f?href=https://www.facebook.com/61571873202957");
}

void GUITypeSudoku::onButtonRelease(int buttonID, Touch* touch)
{
	string packageApp = JNIUtils::getPackageApp();
    game->initAds();
    if (updateGame == 1 || updateGame == 2)
    {
      //  game->showUpdate();
        return;
    }
    /*if (game->message != "")
    {
        game->showMessage();
        return;
    }*/
	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
		onBackKey();

		}

		break;
	case BTN_SOUND_ID:
		{
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png", false);
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png", false);
			}

			UserDefault::getInstance()->setBoolForKey("music", game->music);
			UserDefault::getInstance()->flush();
		}
		break;
    case BTN_NORMAL_ID:
    {
        JNIUtils::sendEvent("game_normal", "1");
        GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().guiSudoku.showGUIWithMode(NORMAL_SUDOKU);
    }
    break;
	case BTN_CHALLENGE_ID:
		{
            JNIUtils::sendEvent("game_level", "1");
		    GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiSudoku.showGUIWithMode(LEVEL_SUDOKU);
		}
		break;
   
    case BTN_UPDATE:
        JNIUtils::openApp(urlUpdate.c_str());
        break;
    case BTN_GAME_ID:
     //  GUIManager::getInstance().showGui(&GUIManager::getInstance().guiLanguage);
       // GUIManager::getInstance().showGui(&GUIManager::getInstance().guiBuyHeart);
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiMinigames);
        break;
	default:
		break;
	}
}

void GUITypeSudoku::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
	BaseGUI::showGUI(parent, hasFog);
	Size size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float sY = size.height - btnBack->getHeight() * 0.7;
	float sX = size.width * 0.5;

	moveVertical(btnBack->normalImage->_img, 0, 400, 0);
	moveVertical(btnSound->normalImage->_img, 0, 400, 0.1);

    moveVertical(btnUpdate->normalImage->_img, 0, 400, 0.1);

	for (int i = 0; i < arrayButton.size(); i++) {
		moveHorizontal(arrayButton.at(i)->normalImage->_img, 0, i % 2 == 0 ? -400 : 400, 0.1 + 0.05 * i);
	}
    btnUpdate->setVisible(updateGame >= 3);
}

void GUITypeSudoku::updateButton()
{

}
