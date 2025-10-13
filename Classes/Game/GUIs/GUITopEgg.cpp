#include "GUITopEgg.h"
#include "TopCell.h"
#include "../Utility/GameSound.h"
#include "Engine/GlobalVar.h"
#include "guiChangeNameEgg.h"
#include "../GUIManager.h"
#include "../Utility/GameUtility.h"
#include "Engine/Utility/LocalizedString.h"
#include "spine/spine-cocos2dx.h"
#include "../Utility/Toast.h"
#include "../Utility/JNIUtils.h"

using namespace spine;
#define BTN_REGISTER 5
#define BTN_CANCEL 8
#define BTN_TOP_SCORE 9
#define BTN_TOP_COUNT 10

#define WIDTH_ROW 383
#define HEIGHT_ROW 60
GUITopEgg::GUITopEgg(void)
{
	setKeypadEnabled(true);
}

GUITopEgg::~GUITopEgg(void)
{
}

void GUITopEgg::initGUI()
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	currentTop = 0;
	isOld = false;
	GameImage* background = addImage("lobby_background.png");
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width / 2, size.height / 2);

	float startY = size.height - 330;
	spine::SkeletonAnimation* skeletonNode = spine::SkeletonAnimation::createWithJsonFile("effect/top/fx_result_win.json", "effect/top/fx_result_win.atlas", 1.0f);
	skeletonNode->setAnimation(0, "fx_result_win_idle", true);
	addChild(skeletonNode);
	skeletonNode->setScale(0.6);
	skeletonNode->setPosition(ccp(size.width * 0.5, startY));

	startY = size.height - 140;
	lbMode = Text::create("1", "fonts/tahomabd.ttf", 22);
	lbMode->enableOutline(ccc4(132, 34, 13, 255), 2);
	lbMode->setTextHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(lbMode);
	lbMode->setAnchorPoint(ccp(0.5, 0.5f));
	lbMode->setPosition(ccp(size.width * 0.5, startY));

	startY = size.height - 170;
	float pad = 20;
	ui::Scale9Sprite *bgList = ui::Scale9Sprite::create("Board/table/top/popup.png");
	float height = startY - size.height * 0.15 - 130;
	bgList->setContentSize(CCSize(WIDTH_ROW + 20, height));
	bgList->setPosition(ccp(size.width * 0.5, startY - bgList->getContentSize().height * 0.5));
	bgList->setOpacity(120);
	addChild(bgList);

	lbEmpty = Text::create(CCLocalizedString("NO_DATA").c_str(), "fonts/tahomabd.ttf", 18);
	lbEmpty->setContentSize(Size(bgList->getContentSize().width * 0.8, 100));
	lbEmpty->setTextAreaSize(Size(bgList->getContentSize().width * 0.8, 100));
	lbEmpty->setTextHorizontalAlignment(TextHAlignment::CENTER);
	bgList->addChild(lbEmpty);
	lbEmpty->setAnchorPoint(ccp(0.5, 0.5f));
	lbEmpty->setPosition(ccp(bgList->getContentSize().width * 0.5, bgList->getContentSize().height * 0.55));

	listTop = TableView::create(this, CCSizeMake(WIDTH_ROW, bgList->getContentSize().height - pad));
	listTop->setDirection(TableView::Direction::VERTICAL);
	listTop->setAnchorPoint(ccp(0.5f, 0));
	//listTop->setContentOffset(ccp(0,0));
	listTop->setPosition(ccp(bgList->getContentSize().width * 0.5f - WIDTH_ROW * 0.5, pad * 0.5));
	listTop->setDelegate(this);
	listTop->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	bgList->addChild(listTop);
	
	ui::Scale9Sprite *bgInfo = ui::Scale9Sprite::create("Board/table/top/popup.png");
	bgInfo->setContentSize(CCSize(300, 110));
	bgInfo->setPosition(ccp(bgInfo->getContentSize().width * 0.5 + size.width * 0.02, bgList->getPositionY() - bgList->getContentSize().height * 0.5 - bgInfo->getContentSize().height * 0.7));
	bgInfo->setOpacity(120);
	addChild(bgInfo);

	Sprite* avatar = Sprite::create("Board/table/avatar/avatar_0.png");
	bgInfo->addChild(avatar);
	avatar->setPosition(avatar->getContentSize().width * 0.8, bgInfo->getContentSize().height * 0.5);

	Sprite* borderAvatar = Sprite::create("Board/table/avatar/level0.png");
	bgInfo->addChild(borderAvatar);
	borderAvatar->setScale(0.9);
	borderAvatar->setPosition(avatar->getPosition());

	lbName = Text::create("1", "fonts/tahomabd.ttf", 16);
	lbName->setTextHorizontalAlignment(TextHAlignment::LEFT);
	bgInfo->addChild(lbName);
	lbName->setAnchorPoint(ccp(0, 0.5f));
	lbName->setPosition(ccp(avatar->getContentSize().width * 0.7 + avatar->getPositionX(), bgInfo->getContentSize().height * 0.8));

	lbScore = Text::create("1", "fonts/tahomabd.ttf", 16);
	lbScore->setTextHorizontalAlignment(TextHAlignment::LEFT);
	bgInfo->addChild(lbScore);
	lbScore->setAnchorPoint(ccp(0, 0.5f));
	lbScore->setPosition(ccp(lbName->getPositionX(), lbName->getPositionY() - 30));

	lbRank = Text::create("1", "fonts/tahomabd.ttf", 16);
	lbRank->setTextHorizontalAlignment(TextHAlignment::LEFT);
	bgInfo->addChild(lbRank);
	lbRank->setAnchorPoint(ccp(0, 0.5f));
	lbRank->setPosition(ccp(lbName->getPositionX(), lbScore->getPositionY() - 30));

	string resource = "btnTop.png";
	btnTop = Button::create(resource, resource, resource);
	btnTop->setPosition(ccp(bgInfo->getContentSize().width - btnTop->getContentSize().width * 0.7, lbRank->getPositionY()));
	bgInfo->addChild(btnTop);

	btnTop->addClickEventListener([this](Ref*) {
		if (highscore > 0) {
			GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChangeNameEgg);
			GUIManager::getInstance().guiChangeNameEgg.currentTop = currentTop;
		}
		else {
			Toast::makeToast(2, "Your score is not acceptable");
			return;
		}
	});

	resource = "Board/table/top/btnEdit.png";
	btnEdit = Button::create(resource, resource, resource);
	btnEdit->setPosition(ccp(bgInfo->getContentSize().width - btnEdit->getContentSize().width * 0.7, lbName->getPositionY()));
	bgInfo->addChild(btnEdit);

	btnEdit->addClickEventListener([this](Ref*) {
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChangeNameEgg);
		GUIManager::getInstance().guiChangeNameEgg.currentTop = currentTop;
	});

	resource = "btnPlay.png";
	btnPlay = Button::create(resource, resource, resource);
	btnPlay->setPosition(ccp(size.width - btnPlay->getContentSize().width * 0.6, bgInfo->getPositionY()));
	addChild(btnPlay);

	btnPlay->addClickEventListener([this](Ref*) {
		switch (currentTop)
		{
		case TOP_NORMAL:
			JNIUtils::sendEvent("choose_game_endless", "1");
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiEgg.showGui(ENDLESS);
			break;
		case TOP_TIME:
			JNIUtils::sendEvent("choose_game_time", "1");
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiEgg.showGui(TIME);
			break;
		case TOP_DROP:
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiMerge.showGUI();
			JNIUtils::sendEvent("choose_game_merge", "1");
			break;
		case TOP_TWENTY:
			GUIManager::getInstance().removeAllGui();
			//GUIManager::getInstance().guiGame.showGui();
			JNIUtils::sendEvent("choose_game_twenty", "1");
			break;
		case TOP_LINE:
			
			break;
		default:
			break;
		}
	});

	resource = "480_800/btnBack.png";
	Button* btnBack = Button::create(resource, resource, resource);
	btnBack->setPosition(ccp(size.width - btnBack->getContentSize().width * 0.7, size.height - btnBack->getContentSize().height * 0.7));
	addChild(btnBack);

	btnBack->addClickEventListener([this](Ref*) {
		onBackKey();
	});
	for (int i = 0; i < 5; i++)
		showNotice[i] = false;

	layerDark = LayerColor::create(ccc4(0, 0, 0, 255), size.width, size.height);
	addChild(layerDark);

	iconTop = Sprite::create("Board/table/top/youAreTop.png");
	addChild(iconTop);
	iconTop->setPosition(ccp(size.width * 0.5, size.height * 0.55));

	lbTop = Text::create("1", "fonts/tahomabd.ttf", 55);
	lbTop->enableOutline(ccc4(240, 20, 20, 255));
	iconTop->addChild(lbTop);
	lbTop->setPosition(ccp(410, 70));

}

void GUITopEgg::onBackKey() {
	if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
	{
		GUIManager::getInstance().removeAllGui();
		GUIManager::getInstance().showGui(&GUIManager::getInstance().guiChoose);
		GUIManager::getInstance().isCallBackPress = true;
	}
}

void GUITopEgg::onButtonRelease(int buttonID, CCTouch* touch)
{
	
}

void GUITopEgg::showTop(int idTop)
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
	highscore = 0;
	if (idTop >= 0)
		currentTop = idTop;
	else
		idTop = currentTop;
	// Kiem tra xem co can phai push lai diem cua minh len khong
	switch (idTop)
	{
	case TOP_NORMAL:
		lbScore->setString("Best: " + GameUtility::standardizeNumber(game->scoreEndless));
		highscore = game->scoreEndless;
		lbMode->setString("Endless Mode");
		break;
	case TOP_TIME:
		lbScore->setString("Best: " + GameUtility::convertTime(game->scoreTime));
		highscore = game->scoreTime;
		lbMode->setString("Time Mode");
		break;
	case TOP_DROP:
		highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highscoreMerge", 0);
		lbScore->setString("Best: " + GameUtility::standardizeNumber(highscore));
		lbMode->setString("Drop Mode");
		break;
	case TOP_TWENTY:
		
		break;
	case TOP_LINE:
		
		break;
	default:
		break;
	}
	game->pushOneTop(idTop);
	reloadMyData();
	reloadTopData();
}

void GUITopEgg::reloadTopData()
{
	listTop->reloadData();
}

void GUITopEgg::insertDone()
{
	// cap nhat du lieu cua minh thanh cong, lay lai du lieu
	game->getTop(currentTop);
	game->getMyTop(currentTop);
}

void GUITopEgg::reloadMyData()
{
	//myInfo->setInfo(game->arrayMyTop[currentTop]);
	if (game->haveTop() == false) {
		lbRank->setString("Rank: ----");
		btnTop->setVisible(true);
		btnEdit->setVisible(false);
		if (game->highscore > 0) {
			btnTop->stopAllActions();
			btnTop->runAction(
				CCRepeatForever::create(
					CCSequence::create(
						CCScaleTo::create(0.2, 1.0),
						CCScaleTo::create(0.2, 0.8),
						NULL
					)
				)
			);
		}
	}
	else {
		string s = "Rank: " + GameUtility::standardizeNumber(game->arrayMyTop[currentTop].index);
		if (game->arrayOldTop[currentTop] < 0) {
			s = s + "";
			lbRank->setColor(ccc3(255, 255, 255));
		}
		else {
			if (game->arrayOldTop[currentTop] >= game->arrayMyTop[currentTop].index) {
				s = s + "(+" + to_string(game->arrayOldTop[currentTop] - game->arrayMyTop[currentTop].index) + ")";
				lbRank->setColor(ccc3(34, 224, 18));
			}
			else {
				s = s + "(" + to_string(game->arrayOldTop[currentTop] - game->arrayMyTop[currentTop].index) + ")";
				lbRank->setColor(ccc3(247, 70, 62));
			}
		}
		lbRank->setString(s);
		btnTop->setVisible(false);
		btnEdit->setVisible(true);
	}
	if (game->namePlayer.compare("") == 0) {
		lbName->setString("No Name");
	}
	else {
		lbName->setString(GameUtility::standardizeString(game->namePlayer, 20));
	}
	layerDark->setVisible(false);
	if (showNotice[currentTop] == false) {
		if (game->arrayMyTop[currentTop].index > 0 && game->arrayMyTop[currentTop].index < 20) {
			iconTop->setVisible(true);
			Toast::makeToast(2.0, ("Welcome top " + to_string(game->arrayMyTop[currentTop].index) + " Server").c_str());
			showNotice[currentTop] = true;
			lbTop->setString(GameUtility::toString(game->arrayMyTop[currentTop].index));
			iconTop->setPositionX(-iconTop->getContentSize().width * 0.5);
			CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
			iconTop->stopAllActions();
			iconTop->runAction(
				CCSequence::create(
					CCEaseBackOut::create(CCMoveTo::create(0.5, ccp(size.width * 0.5, iconTop->getPositionY()))),
					CCDelayTime::create(1.5),
					CCEaseBackIn::create(CCMoveTo::create(0.5, ccp(size.width + iconTop->getContentSize().width * 0.5, iconTop->getPositionY()))),
					NULL
				)
			);
			layerDark->stopAllActions();
			layerDark->setVisible(true);
			layerDark->setOpacity(0);
			layerDark->runAction(
				CCSequence::create(
					CCEaseExponentialOut::create(CCFadeTo::create(0.5, 180)),
					CCDelayTime::create(1.5),
					CCFadeOut::create(0.5),
					NULL
				)
			);
			lbTop->stopAllActions();
			lbTop->setScale(0);
			lbTop->runAction(
				CCSequence::create(
					CCDelayTime::create(0.6),
					CCEaseBackOut::create(CCScaleTo::create(0.5, 1)),
					NULL
				)
			);
		}
		else {
			iconTop->setVisible(false);
		}
	}
	else {
		iconTop->setVisible(false);
	}
}

void GUITopEgg::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());

}
cocos2d::CCSize GUITopEgg::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return CCSizeMake(WIDTH_ROW, HEIGHT_ROW);
}
cocos2d::extension::TableViewCell* GUITopEgg::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	TopCell *cell = (TopCell*)table->dequeueCell();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	if (!cell) {
		cell = new TopCell();
		cell->autorelease();
	}
	cell->setInfo(game->arrayTop[currentTop][idx]);
	return cell;
}

ssize_t GUITopEgg::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	lbEmpty->setVisible(game->arrayTop[currentTop].size() == 0);
	return game->arrayTop[currentTop].size();
}
std::string GUITopEgg::className = "GUITopEgg";

