#include "GUIMinigames.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../../Engine/Utility/LocalizedString.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/CStringUtils.h"
#include "../Utility/GameSound.h"
#include "Game/Data/GlobalData.h"
#include "MainScene.h"

#define BACKGROUND_RES "loading/bgPortalCenterZP.jpg"
#define PROGRESS_RES "loading/bgProgress.png"
#define ICON_GAME "loading/iconGame.png"
#define BG_PROGRESS "loading/black.png"

#define BTN_UPDATE_ID 33
#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_NORMAL_ID 3
#define BTN_TIME_ID 4
#define BTN_OLD_VERSION 5
#define BTN_EXTRA_ID 6
#define BTN_SETTING 7
#define BTN_LEVEL 8
#define BTN_BLOCK_ID 9
#define BTN_ONLINE_ID 10
#define BTN_CHALLENGE_ID 11
#define BTN_GAME 19
#define BTN_TWENTY 20
#define BTN_EGG 21
#define BTN_BUBBLE 22
#define BTN_DROP 23
#define BTN_CAPSA_SUSUN 24
#define BTN_POP 25
#define BTN_BOMB 26
#define BTN_CHESS 27
#define BTN_LINE 28

#define GAME_EGG         0
#define GAME_BLOCK       1
#define GAME_PIKA        2
#define GAME_SUDOKU		 3
#define GAME_2048		 4
#define GAME_DROP        5
#define GAME_BRICK       6
#define GAME_LINE        7
#define GAME_BOMB        8
#define GAME_POP         9
#define GAME_TWENTY      10
#define GAME_BUBBLE      11
#define GAME_CHESS       100
#define GAME_SOLITAIRE     19
#define GAME_CARO 10



GUIMinigames::GUIMinigames(void) : BaseGUI()
{
	BaseGUI();
	setKeypadEnabled(true);
}

GUIMinigames::~GUIMinigames(void)
{

}

void GUIMinigames::initGUI(){
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    callBackSplash();
}

void GUIMinigames::onBackKey(){
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		//GUIManager::getInstance().removeAllGui();
		//GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChoose);
		GUIManager::getInstance().isCallBackPress = true;
        game->endGame();
	}
}


void GUIMinigames::callBackSplash()
{

	BaseGUI::initGUI();
	JNIUtils::crashlyticSetString("LobbyGUI", "Start Init");
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	GameImage* background = addImage("background.jpg");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	DBCCFactory::getInstance()->loadDragonBonesData("effect/StarTimer/skeleton.xml", "StarTimer");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/StarTimer/texture.plist", "StarTimer");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/no_top/skeleton.xml", "no_top");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/no_top/texture.plist", "no_top");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/tile_light/skeleton.xml", "tile_light");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/tile_light/texture.plist", "tile_light");

	DBCCFactory::getInstance()->loadDragonBonesData("effect/fire_work/skeleton.xml", "fire_work");
	DBCCFactory::getInstance()->loadTextureAtlas("effect/fire_work/texture.plist", "fire_work");

	DBCCFactory::getInstance()->loadDragonBonesData("Chest/skeleton.xml", "Chest");
	DBCCFactory::getInstance()->loadTextureAtlas("Chest/texture.plist", "Chest");


	btnBack = addButton(BTN_BACK_ID, "btnBack.png", new BubbleBehavior(), NULL, false);
	btnBack->setPosition(size.width - btnBack->getWidth() * 0.7f, size.height - btnBack->getHeight() * 0.7f);
    
    btnUpdate = addButton(BTN_UPDATE_ID, "btnUpdate.png", new BubbleBehavior(), NULL, false);
    btnUpdate->setPosition(btnUpdate->getWidth() * 0.5f, btnBack->getPositionY() - 30);
    btnUpdate->normalImage->setScale(0.8);
    btnUpdate->setVisible(updateGame > 2);

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

    int numGame = 11;

	btnBlock = addButton(BTN_GAME, "iconGameBlock.png", new BubbleBehavior(), NULL, false);
	btnBlock->setPosition(size.width * 0.5, btnBack->getPositionY() - btnBlock->getHeight() * 0.5 - btnBack->getHeight() * 0.5);
	//btnBlock->setVisible(false);

	float padY = 240;
	float heightBg = btnBlock->getPositionY() - btnBlock->getHeight() * 0.6 - size.height * 0.15;
    game->extendGame = false;
	
    numGame = 11;

	bgGame = Scale9Sprite::create("IconGame/popup.png");
	addChild(bgGame);
	bgGame->setPosition(size.width * 0.5, size.height * 0.15 + heightBg * 0.5);
	bgGame->setContentSize(Size(size.width * 0.98, heightBg));
	bgGame->setOpacity(50);

    int numRow = ceil(numGame * 1.0 / 2);
	scrollView = cocos2d::extension::ScrollView::create();
    scrollView->setTouchEnabled(true);
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    scrollView->setSwallowTouches(false);
    scrollView->setContentSize(size);
	float heightList = padY * numRow;
    scrollView->setContentSize(CCSize(bgGame->getContentSize().width, heightList));
	scrollView->setViewSize(CCSizeMake(bgGame->getContentSize().width, bgGame->getContentSize().height * 0.95));
	scrollView->setPosition(bgGame->getPositionX() - scrollView->getContentSize().width * 0.5, bgGame->getPositionY() - bgGame->getContentSize().height * 0.5 + 5);
   // scrollView->addChild(imageView);
	scrollView->setContentOffsetInDuration(Vec2(0, scrollView->getViewSize().height - heightList), 0);
	addChild(scrollView);
    scrollView->setDelegate(this);

	string arrayResource[12] = {"", "", "", "", "", "", "", ""};
	string arrayName[12] = {"", "", "", "", "", "", "", ""};
	arrayResource[GAME_LINE] = "IconGame/iconLine.png";
	arrayResource[GAME_POP] = "IconGame/iconPop.png";
	arrayResource[GAME_DROP] = "IconGame/iconDrop.png";
	arrayResource[GAME_TWENTY] = "IconGame/icon24.png";
	arrayResource[GAME_BOMB] = "IconGame/iconBomb.png";
	arrayResource[GAME_BUBBLE] = "IconGame/iconBubble.png";
    arrayResource[GAME_BLOCK] = "IconGame/iconBlock.png";
	//arrayResource[GAME_CHESS] = "IconGame/iconChess.png";
    arrayResource[GAME_EGG] = "IconGame/iconEgg.png";
	//arrayResource[GAME_SOLITAIRE] = "IconGame/iconSolaitre.png";
    arrayResource[GAME_PIKA] = "IconGame/iconPika.png";
	arrayResource[GAME_BRICK] = "IconGame/iconBrick.png";
	arrayResource[GAME_SUDOKU] = "IconGame/iconSudoku.png";
	arrayResource[GAME_2048] = "IconGame/icon2048.png";

	arrayName[GAME_LINE] = "Color Lines - Arraange 5 balls to get score";
	arrayName[GAME_POP] = "Pop out Number - Touch to combine number";
	arrayName[GAME_DROP] = "Drop Number - Drop number to get higher number";
	//arrayName[GAME_TWENTY] = "Twenty - Merge number to make 20";
	arrayName[GAME_BOMB] = "Minesweeper - Find all boms on the map";
	arrayName[GAME_BUBBLE] = "Connect Bubble - Combine the same bubbles";
    arrayName[GAME_BLOCK] = "Block Puzzel - Connect Block to get score";
	//arrayName[GAME_CHESS] = "Co Tuong - Challenge your brain";
    
	int arrayGame1[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	for (int i = 0; i < numGame; i++)
	{
		// check if i in vector arrayIdGame
		if (std::find(game->arrayIdGame.begin(), game->arrayIdGame.end(), arrayGame1[i]) == game->arrayIdGame.end())
		{
			// insert at begin of vector arrayIdGame
			game->arrayIdGame.insert(game->arrayIdGame.begin(), arrayGame1[i]);
		}
	}
    
    for (int i = 0; i < numGame; i++) {
       // s = arrayResource[i];
		int idGame = game->arrayIdGame.at(i);
        Button* buttonGame = Button::create();
        buttonGame->setTouchEnabled(true);
        buttonGame->setTag(idGame);
        buttonGame->loadTextures(arrayResource[idGame], arrayResource[idGame], arrayResource[idGame]);
      //  button->setPosition(ccp(50, 50));
        scrollView->addChild(buttonGame);
        buttonGame->addTouchEventListener(this, toucheventselector(GUIMinigames::onTouchBegan));
        buttonGame->setSwallowTouches(false);
		int row = numRow - 1 - floor(i / 2.0);
		int column = i % 2;
        buttonGame->setPosition(Vec2(scrollView->getContentSize().width * 0.5 + (buttonGame->getContentSize().width * 0.5 + 20) * (column == 1 ? 1 : -1), padY * (row + 0.5)));
        
        if (idGame == GAME_PIKA) {
//            Sprite* iconHot = Sprite::create("IconGame/iconHot.png");
//            buttonGame->addChild(iconHot);
//            iconHot->setPosition(buttonGame->getContentSize().width * 0.9, buttonGame->getContentSize().height * 0.9);
        }
		arrayButtonGame.push_back(buttonGame);
    }
	countScroll = 0;
}

void GUIMinigames::onButtonRelease(int buttonID, CCTouch* touch)
{
	//GUIManager::getInstance().guiLoadingAds.showAds(false);
	//return;

	switch (buttonID)
	{
            GameSound::playClick();
	case BTN_BACK_ID:
		{
		onBackKey();
		}
		
		break;
        case BTN_UPDATE_ID:
            {
                JNIUtils::openApp(urlUpdate.c_str());
            }
            
            break;
	case BTN_SOUND_ID:
		{
       //     GUIManager::getInstance().guiLoadingAds.showAds(false);
		//playEgg();
			game->music = !game->music;
			if(game->music)
			{
				btnSound->normalImage->setImage("btnSoundOn.png", false);
			}
			else
			{
				btnSound->normalImage->setImage("btnSoundOff.png", false);
			}

			CCUserDefault::sharedUserDefault()->setBoolForKey("music", game->music);
			CCUserDefault::sharedUserDefault()->flush();
		}
		break;
		case BTN_CHESS:
		{
			
		}
		break;
		case BTN_GAME:
		{
			game->loadPlayNormal();
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiLine.showGuiWithMode(0);
		}
		break;
		case BTN_EGG:
		{
			playEgg();
		}
		break;
	default:
		break;
	}
}

void GUIMinigames::sendData(int mode) {
	
}


void GUIMinigames::showGUI(CCNode* parent /* = NULL */, bool hasFog /* = true */)
{
	if (game->isInitAds)
		game->showAdsFull();
    
	game->initAds();
	countScroll = 0;
	BaseGUI::showGUI(parent, hasFog);
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	float sY = size.height - btnBack->getHeight() * 0.7;
	float sX = size.width * 0.5;
    btnUpdate->setVisible(updateGame > 2);
	moveVertical(btnBack->normalImage->_img, 0, 400, 0);
	moveVertical(btnSound->normalImage->_img, 0, 400, 0.1);
    moveVertical(btnBlock->normalImage->_img, 0, 400, 0.2);

	for (int i = 0; i < arrayButtonGame.size(); i++) {
		int column = i % 2;
		arrayButtonGame.at(i)->setPositionX(
			scrollView->getContentSize().width * 0.5 +
			(arrayButtonGame.at(i)->getContentSize().width * 0.5 + 15) * (column == 1 ? 1 : -1)
		);
		moveHorizontal(arrayButtonGame.at(i), arrayButtonGame.at(i)->getPositionX(), i % 2 == 0 ? -400 : 400,
			0.1 + 0.05 * i);
	}
    
}

void GUIMinigames::playBlock()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().showGui(&GUIManager::getInstance().guiGame);
	
	if (game->numPlayBlock < 12) {
		game->numPlayBlock++;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("numPlayBlock", game->numPlayBlock);
	}
}

void GUIMinigames::playTwenty()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().guiTwenty.showGui();
	
}

void GUIMinigames::playEgg()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().guiEgg.showGui(ENDLESS);

	
}


void GUIMinigames::playBubble()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
	//GUIManager::getInstance().guiBubble.showGui(
	GUIManager::getInstance().guiBubble.showGui();
	
	
}

void GUIMinigames::playBomb()
{
	game->timePlayGame = 0;
	GUIManager::getInstance().removeAllGui();
	//GUIManager::getInstance().guiBubble.showGui(
	GUIManager::getInstance().guiBomb.showGUI();
	
	if (game->numPlayBomb < 12) {
		game->numPlayBomb++;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("numPlayBomb", game->numPlayBomb);
		CCUserDefault::sharedUserDefault()->flush();
	}
}

void GUIMinigames::updateButton()
{
	
//	btnCapsa->setVisible(false);
}

void GUIMinigames::onTouchBegan(CCObject *pSender, TouchEventType type) {
	CCLOG("touch ne ");    
    if (!game->isInitAds) {
        JNIUtils::initAds("ca-app-pub-3500982632045294~6744827086", "ca-app-pub-3500982632045294/4113145105", "ca-app-pub-3500982632045294/2800063431", idAdsBanner, idAdsFull);
        game->isInitAds = true;
    }
    
	
    
    Button* btn = dynamic_cast<Button*>(pSender);
    switch (type) {
        case TouchEventType::TOUCH_EVENT_BEGAN:
			countScroll = 0;
            break;
		case TouchEventType::TOUCH_EVENT_ENDED: {
			if (countScroll > 5) {
				countScroll = 0;
				return;
			}
			countScroll = 0;
			int buttonId = btn->getTag();
            JNIUtils::sendEvent(("minigame_" + to_string(buttonId)).c_str(), "1");
            // move buttonId to Top of vector game->arrayIdGame
            auto it = std::find(game->arrayIdGame.begin(), game->arrayIdGame.end(), buttonId);
            if (it != game->arrayIdGame.end())
            {
                game->arrayIdGame.erase(it);
            }
            game->arrayIdGame.insert(game->arrayIdGame.begin(), buttonId);
            // make string contains idGame in vector game->arrayIdGame, split by ','
            string s = "";
            for (int i = 0; i < game->arrayIdGame.size(); i++)
            {
                s += to_string(game->arrayIdGame.at(i));
                if (i < game->arrayIdGame.size() - 1)
                {
                    s += ",";
                }
            }
            // and save to UserDefault
            UserDefault::getInstance()->setStringForKey("arrayIdGame", s);
            UserDefault::getInstance()->flush();
			switch (buttonId) {
				case GAME_POP: {
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().guiPop.showGUI();
				}
				break;
				case GAME_LINE: {
                    game->loadPlayNormal();
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().guiLine.showGuiWithMode(0);
				}
				break;
				case GAME_DROP: {
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().guiMerge.showGUI();
				}
				break;
				case GAME_BLOCK: {
				//	playTwenty();
					game->loadBlock();
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().guiGame.showGUI();
				}
				break;
                case GAME_TWENTY: {
					game->loadTwenty();
                    playTwenty();
                    
                }
                break;
				case GAME_BOMB:
					game->loadBomb();
					playBomb();
				break;
				case GAME_BUBBLE:
					game->loadBubble();
					playBubble();
				break;
                case GAME_CHESS:
                    
                break;
				case GAME_EGG:
					game->loadEgg();
					playEgg();
					break;
                case GAME_PIKA:
                {
                    JNIUtils::showAdsBanner(0);
                    game->loadPika();
                    JNIUtils::changeToLandscape();
                    auto director = Director::getInstance();
                    auto glview = director->getOpenGLView();
                    
                    Size frameSize = glview->getFrameSize();
                    glview->setFrameSize(frameSize.height, frameSize.width);
                    if ((frameSize.height / frameSize.width) < (3.0f / 2.0f))
                    {
                        glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_WIDTH);
                    }
                    else
                    {
                        glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_HEIGHT);
                    }
                    GUIManager::getInstance().removeAllGui();
                    GUIManager::getInstance().guiPikachu.showGui(GameMode::NORMAL_MODE);
                    break;
                }
				case GAME_SOLITAIRE:
				{
				//	JNIUtils::loadAdsFullCard();
					JNIUtils::changeToLandscape();

					auto director = Director::getInstance();
					auto glview = director->getOpenGLView();

					Size frameSize = glview->getFrameSize();
					glview->setFrameSize(frameSize.height, frameSize.width);
					if ((frameSize.height / frameSize.width) < (3.0f / 2.0f))
					{
						glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_WIDTH);
					}
					else
					{
						glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_HEIGHT);
					}
				//	sceneMgr->openScene(ChooseGameScene::className);
				//	game->enterCard = true;
				//	CCUserDefault::sharedUserDefault()->setBoolForKey("enterCard", true);
					//CCUserDefault::sharedUserDefault()->flush();
                    break;
				}
				case GAME_BRICK:
				{
					game->loadBrick();
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().showGui(&GUIManager::getInstance().guiBrick);
				}
				break;
				case GAME_SUDOKU:
				{
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().showGui(&GUIManager::getInstance().guiSudoku);
				}
				break;
				case GAME_2048:
				{
					GUIManager::getInstance().removeAllGui();
					GUIManager::getInstance().showGui(&GUIManager::getInstance().gui2048);
				}
				break;
				default:
            	break;
			}
		}
        default:
            break;
    }
}

void GUIMinigames::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
    CCLOG("Dis scroll");
	countScroll++;
}

void GUIMinigames::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {
  //  CCLOG("Did Zoom");
}

void GUIMinigames::onEnter() {
    BaseGUI::onEnter();
    cocos2d::Layer* layer = (Layer*)mainScene->getChildByTag(104);
    layer->unscheduleAllCallbacks();
    layer->schedule(schedule_selector(MainScene::update), 0);

}

bool GUIMinigames::onTouchBegan( CCTouch*touch, CCEvent* event )
{
    Vec2 p = touch->getLocation();
    if (p.y > bgGame->getPosition().y + bgGame->getContentSize().height * 0.5) {
        countScroll = 10;
    }
    return BaseGUI::onTouchBegan(touch, event);
}
