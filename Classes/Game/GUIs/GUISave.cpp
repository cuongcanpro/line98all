#include "GUISave.h"
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

#define BTN_SAVE_BACK 1



GUISave::GUISave(void) : BaseGUI()
{
	BaseGUI();

	setKeypadEnabled(true);
}


GUISave::~GUISave(void)
{
}


void GUISave::initGUI(){
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

void GUISave::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().isCallBackPress = true;
		GUIManager::getInstance().removeFromListGui();
	}
}


void GUISave::callBackSplash()
{
	BaseGUI::initGUI();

	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);
	//
	//	
	//	LabelBM* label = LabelBM::create("Choose ball's type that you want to play", FONT_NORMAL_TYPE);
	//	label->setWidth(size.width * 0.9);
	//	label->setPosition(size.width * 0.5, background->getPositionY() + background->getRealHeight() * 0.3);
	////	label->setScale(0.8);
	//	this->addChild(label);
	//
	BaseButton* btn = addButton(BTN_SAVE_BACK, "btnBack.png", new BubbleBehavior(), NULL, true);
	if (game->isIOS() && size.width / size.height < 11.0 / 20.0) {
		btn->setPosition(size.width - btn->getWidth() * 0.7f, size.height - btn->getHeight() * 1.5f);
	}
	else {
		btn->setPosition(size.width - btn->getWidth() * 0.7f, size.height - btn->getHeight() * 0.7f);
	}

	lbContent = Label::createWithTTF("New Ball", "fonts/tahomabd.ttf", 22);
	addChild(lbContent);
	//lbContent->setScale(0.7);
	lbContent->setPosition(size.width * 0.5, btn->getPositionY() - 40);

	for (int i = 0; i < 6; i++) {
		float posX, posY;
		posX = i % 2 == 0 ? size.width * 0.25 : size.width * 0.75;
		miniBoard[i] = new MiniBoard("bkg.png", true);
		addChild(miniBoard[i]);
		miniBoard[i]->setScale(0.33);

		arrayBtnSave[i] = addButton(10 + i, "btnSave.png", new BubbleBehavior(), NULL, true);
		arrayBtnSave[i]->setPosition(posX, lbContent->getPositionY() - miniBoard[i]->getRealHeight() * 0.6 - miniBoard[i]->getRealHeight() * 1.25 * (floor(i / 2)));

		arrayBtnUnSave[i] = addButton(20 + i, "btnDelete.png", new BubbleBehavior(), NULL, true);
		arrayBtnUnSave[i]->setPosition(arrayBtnSave[i]->getPositionX() - 30, arrayBtnSave[i]->getPositionY() - 50);

		arrayBtnPlay[i] = addButton(30 + i, "btnPlay.png", new BubbleBehavior(), NULL, true);
		arrayBtnPlay[i]->setPosition(arrayBtnSave[i]->getPositionX() + 30, arrayBtnUnSave[i]->getPositionY());


		miniBoard[i]->setPosition(arrayBtnSave[i]->getPosition());
		miniBoard[i]->loadArrayBall(game->data);

		arrayLbScore[i] = LabelBM::create("New Ball", FONT_GAME_TYPE);
		arrayLbScore[i]->setScale(0.5);
		addChild(arrayLbScore[i]);
		arrayLbScore[i]->setPosition(posX, miniBoard[i]->getPositionY() - miniBoard[i]->getRealHeight() * 0.6);
		//lb->setScale(0.5);
	}
}




void GUISave::showGUI(bool isSave)
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);

	bool add = false;
	bool haveSaveGame = false;
	bool haveEmpty = false;
	if (game->isPlaying == false) {
		isSave = false;
	}
	
	if (isSave == true) {
		
		for (int i = 0; i < 6; i++) {
			if (game->arrayScoreSave[i] >= 0) {
				bool same = true;
				for (int j = 0; j < 81; j++) {
					if (game->arrayDataSave[i][j] != game->data[j]) {
						same = false;
						break;
					}
				}
				if (same) {
					isSave = false;
					break;
				}
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		if (game->arrayScoreSave[i] >= 0) {
			miniBoard[i]->setVisible(true);
			arrayBtnSave[i]->setVisible(false);
			arrayBtnPlay[i]->setVisible(true);
			arrayBtnUnSave[i]->setVisible(true);
			arrayLbScore[i]->setVisible(true);
			arrayLbScore[i]->setString("Score: " + GameUtility::toString(game->arrayScoreSave[i]) + " (" + game->arrayDate[i] + ")");
			miniBoard[i]->loadArrayBall(game->arrayDataSave[i]);
			if (isSave == false) {
			//	arrayBtnPlay[i]->normalImage->stopAllActions();
				//arrayBtnPlay[i]->normalImage->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2, 1.2), CCScaleTo::create(0.2, 1.0), NULL)));
			}
			haveSaveGame = true;
		}
		else {
			haveEmpty = true;
			if (add == false && isSave) {
				miniBoard[i]->setVisible(true);
				arrayBtnPlay[i]->setVisible(false);
				arrayBtnUnSave[i]->setVisible(false);
				arrayBtnSave[i]->setVisible(true);
				miniBoard[i]->loadArrayBall(game->data);
				arrayLbScore[i]->setVisible(true);
				arrayLbScore[i]->setString("Score: " + GameUtility::toString(game->saveScore));
				arrayBtnSave[i]->normalImage->stopAllActions();
				arrayBtnSave[i]->normalImage->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2, 1.2), CCScaleTo::create(0.2, 1.0), NULL)));
				add = true;
			}
			else {
				miniBoard[i]->setVisible(true);
				miniBoard[i]->resetData();
				arrayBtnPlay[i]->setVisible(false);
				arrayBtnUnSave[i]->setVisible(false);
				arrayBtnSave[i]->setVisible(false);
				arrayLbScore[i]->setVisible(false);
			}
		}
		
	}

	if (isSave) {
		if (haveEmpty) {
			this->lbContent->setString(CCLocalizedString("SAVE_GAME").c_str());
		}
	}
	else {
		if (haveSaveGame == false) {
			this->lbContent->setString(CCLocalizedString("NO_SAVE_GAME").c_str());
		}
		else {
			this->lbContent->setString(CCLocalizedString("SELECT_GAME").c_str());
		}
	}
}

void okPlaySave() {
	GUIManager::getInstance().removeFromListGui();
	int index = GUIManager::getInstance().guiSave.currentIndex;
	if (GUIManager::getInstance().guiLine.isInitted() && GUIManager::getInstance().guiLine.isVisible())
		GUIManager::getInstance().guiLine.showGuiWithData(game->arrayDataSave[index], game->arrayScoreSave[index]);
	
	game->showAdsFull();
}


void GUISave::onButtonRelease(int buttonID, CCTouch* touch)
{
	GameSound::playClick();
	string s;
	int index;
	int score;
	switch (buttonID)
	{
            
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	{
		// save data
		s = "";
		index = buttonID - 10;
		score = game->saveScore;
		for (int i = 0; i <81; i++)
		{
				if (i == 0)
				{
					s = s + GameUtility::toString(game->data[i]);
				}
				else
				{
					s = s + "," + GameUtility::toString(game->data[i]);
				}
				game->arrayDataSave[index][i] = game->data[i];
		}
		
		time_t now = time(0);
		tm *ltm = localtime(&now);

		string s1 =  GameUtility::toString(ltm->tm_mday) + "/" +  GameUtility::toString(1 + ltm->tm_mon) + "/" + GameUtility::toString(1900 + ltm->tm_year);
		string day = CCUserDefault::sharedUserDefault()->getStringForKey("daySupport", "");
		CCUserDefault::sharedUserDefault()->setIntegerForKey(("arrayScoreSave" + GameUtility::toString(index)).c_str(), score);
		CCUserDefault::sharedUserDefault()->setStringForKey(("arrayDataSave" + GameUtility::toString(index)).c_str(), s);
		CCUserDefault::sharedUserDefault()->setStringForKey(("arrayDate" + GameUtility::toString(index)).c_str(), s1);
		CCUserDefault::sharedUserDefault()->flush();
		game->arrayDate[index] = s1;
		game->arrayScoreSave[index] = score;
		arrayBtnSave[index]->setVisible(false);
		arrayBtnUnSave[index]->setVisible(true);
		arrayBtnPlay[index]->setVisible(true);
		break;
	}
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	{
		index = buttonID - 20;
		CCUserDefault::sharedUserDefault()->setIntegerForKey(("arrayScoreSave" + GameUtility::toString(index)).c_str(), -1);
		CCUserDefault::sharedUserDefault()->flush();
		game->arrayScoreSave[index] = -1;
		arrayBtnSave[index]->setVisible(false);
		arrayBtnUnSave[index]->setVisible(false);
		arrayBtnPlay[index]->setVisible(false);
		miniBoard[index]->setVisible(false);
		break;
	}
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	{
		GUIManager::getInstance().guiDialog.showGUI(CCLocalizedString("LOSE_GAME").c_str(), &okPlaySave, false, NULL);
		currentIndex = buttonID - 30;
		break;
	}
	case BTN_SAVE_BACK:
		GUIManager::getInstance().removeFromListGui();
		break;
	
	}
}
