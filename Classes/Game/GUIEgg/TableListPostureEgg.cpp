#include "TableListPostureEgg.h"
#include "Engine/GUI/GameImage.h"
#include "Game/Utility/GameUtility.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Engine/Utility/LocalizedString.h"
#include "../Utility/JNIUtils.h"
#include "Game/Utility/GameUtility.h"

TableListPostureEgg::TableListPostureEgg(void)
{
}


TableListPostureEgg::~TableListPostureEgg(void)
{
}

void TableListPostureEgg::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	
}
cocos2d::CCSize TableListPostureEgg::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	return CCSizeMake(size.width * 0.8f, 150);
}
cocos2d::extension::TableViewCell* TableListPostureEgg::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	TableViewCell *cell = table->dequeueCell();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	size.setSize(size.width * 0.8f, 50);

	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();
		cell->setTag(arrayButton.size() / 3);
		CCMenuItemImage *btnResult = CCMenuItemImage::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3) + ".png").c_str()).c_str(), 
			ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3) + ".png").c_str()).c_str(), this, menu_selector(TableListPostureEgg::resultCallback));
		float pad = (size.width - btnResult->getContentSize().width * 3) / 2;
		btnResult->setPosition(ccp(btnResult->getContentSize().width * 0.5f, 90));
		btnResult->setTag(idx * 3 + 1);
		btnResult->setVisible(false);
		//btnResult->setSwallowTouch

		Button* btn = Button::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3) + ".png").c_str()).c_str(), ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3) + ".png").c_str()).c_str()
			, ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3) + ".png").c_str()).c_str());
		cell->addChild(btn);
		btn->setSwallowTouches(false);
		btn->setTag(idx * 3 + 1);
		btn->addClickEventListener([this](Ref* sender)
		{
			Button* bt = static_cast <Button*> (sender);
			selectLevel(bt->getTag());
			/*GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiLoading.showGui(bt->getTag());
			JNIUtils::sendEvent("choose_level", GameUtility::toString(bt->getTag()).c_str());*/
		});
		btn->setPosition(ccp(btn->getContentSize().width * 0.5f, 90));

		Sprite* iconLock = Sprite::create("480_800/egg/iconLocker.png");
		cell->addChild(iconLock);
		iconLock->setTag(201);
		iconLock->setPosition(btn->getPositionX(), btn->getPositionY());

		//Button

		LabelBM *lb = LabelBM::create(("Level " + GameUtility::toString(idx * 3 + 1)).c_str(), FONT_NORMAL_TYPE);
		cell->addChild(lb);
		lb->setTag(100);
		lb->setPos(btn->getPositionX(), btn->getPositionY() - btn->getContentSize().height * 0.7f);

		CCMenuItemImage *btnResult1 = CCMenuItemImage::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3 + 1) + ".png").c_str()).c_str(), 
			ScreenUtils::fileFull(("legg/evel_" + GameUtility::toString((int)idx * 3 + 1) + ".png").c_str()).c_str(), this, menu_selector(TableListPostureEgg::resultCallback));
		btnResult1->setPosition(ccp(btnResult->getContentSize().width * 1.5f + pad, btnResult->getPositionY()));
		btnResult1->setTag(idx * 3 + 2);
		btnResult1->setVisible(false);

		Button* btn1 = Button::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3 + 1) + ".png").c_str()).c_str(), ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3 + 1) + ".png").c_str()).c_str()
			, ScreenUtils::fileFull(("egg/level_" + GameUtility::toString((int)idx * 3 + 1) + ".png").c_str()).c_str());
		cell->addChild(btn1);
		btn1->setSwallowTouches(false);
		btn1->setTag(idx * 3 + 2);
		btn1->addClickEventListener([this](Ref* sender)
		{
			Button* bt = static_cast <Button*> (sender);/*
			GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiLoading.showGui(bt->getTag());
			JNIUtils::sendEvent("choose_level", GameUtility::toString(bt->getTag()).c_str());*/
			selectLevel(bt->getTag());
		});
		btn1->setPosition(ccp(btn->getContentSize().width * 1.5f + pad, btn->getPositionY()));

		iconLock = Sprite::create("480_800/egg/iconLocker.png");
		cell->addChild(iconLock);
		iconLock->setTag(202);
		iconLock->setPosition(btn1->getPositionX(), btn1->getPositionY());

		lb = LabelBM::create(("Level " + GameUtility::toString(idx * 3 + 2)).c_str(), FONT_NORMAL_TYPE);
		cell->addChild(lb);
		lb->setTag(101);
		lb->setPos(btn1->getPositionX(), btn1->getPositionY() - btn1->getContentSize().height * 0.7f);

		int convert = (int)idx * 3 + 2;
		if (convert >= 20) {
			convert = 19;
		}

		CCMenuItemImage *btnResult2 = CCMenuItemImage::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString(convert) + ".png").c_str()).c_str(), 
			ScreenUtils::fileFull(("egg/level_" + GameUtility::toString(convert) + ".png").c_str()).c_str(), this, menu_selector(TableListPostureEgg::resultCallback));
		btnResult2->setPosition(ccp(btnResult->getContentSize().width * 2.5f + 2*pad, btnResult->getPositionY()));
		btnResult2->setTag(idx * 3 + 3);
		btnResult2->setVisible(false);

		Button* btn2 = Button::create(ScreenUtils::fileFull(("egg/level_" + GameUtility::toString(convert) + ".png").c_str()).c_str(), ScreenUtils::fileFull(("egg/level_" + GameUtility::toString(convert) + ".png").c_str()).c_str()
			, ScreenUtils::fileFull(("egg/level_" + GameUtility::toString(convert) + ".png").c_str()).c_str());
		cell->addChild(btn2);
		btn2->setSwallowTouches(false);
		btn2->setTag(idx * 3 + 3);
		btn2->addClickEventListener([this](Ref* sender)
		{
			Button* bt = static_cast <Button*> (sender);
			selectLevel(bt->getTag());
			/*GUIManager::getInstance().removeAllGui();
			GUIManager::getInstance().guiLoading.showGui(bt->getTag());
			JNIUtils::sendEvent("choose_level", GameUtility::toString(bt->getTag()).c_str());*/
		});
		btn2->setPosition(ccp(btn->getContentSize().width * 2.5f + 2 * pad, btn->getPositionY()));
		iconLock = Sprite::create("480_800/egg/iconLocker.png");
		cell->addChild(iconLock);
		iconLock->setTag(203);
		iconLock->setPosition(btn2->getPositionX(), btn2->getPositionY());

		lb = LabelBM::create(("Level " + GameUtility::toString(idx * 3 + 3)).c_str(), FONT_NORMAL_TYPE);
		cell->addChild(lb);
		lb->setTag(102);
		lb->setPos(btn2->getPositionX(), btn2->getPositionY() - btn2->getContentSize().height * 0.7f);

		arrayButton.push_back(btn);
		arrayButton.push_back(btn1);
		arrayButton.push_back(btn2);
		CCMenu *menu = CCMenu::create(btnResult, btnResult1, btnResult2, NULL);
		cell->addChild(menu);
		menu->setPosition(ccp(0, 0));
		menu->setTag(6);

		if(idx == 6)
			btn2->setVisible(false);
	}
//	else
//	{
		int id = cell->getTag();
		Button* btn1 = arrayButton.at(id * 3);
		Button* btn2 = arrayButton.at(id * 3 + 1);
		Button* btn3 = arrayButton.at(id * 3 + 2);

		string s = "480_800/egg/level_" + GameUtility::toString((int)idx * 3 + 0) + ".png";
		btn1->loadTextures(s, s, s);

		s = "480_800/egg/level_" + GameUtility::toString((int)idx * 3 + 1) + ".png";
		btn2->loadTextures(s, s, s);

		s = "480_800/egg/level_" + GameUtility::toString((int)idx * 3 + 2) + ".png";
		btn3->loadTextures(s, s, s);

		btn1->setTag(idx * 3 + 1);
		btn2->setTag(idx * 3 + 2);
		btn3->setTag(idx * 3 + 3);

		LabelBM* lb = (LabelBM*)cell->getChildByTag(100);
		lb->setText(("Level " + GameUtility::toString(idx * 3 + 1)).c_str());

		lb = (LabelBM*)cell->getChildByTag(101);
		lb->setText(("Level " + GameUtility::toString(idx * 3 + 2)).c_str());

		lb = (LabelBM*)cell->getChildByTag(102);
		lb->setText(("Level " + GameUtility::toString(idx * 3 + 3)).c_str());
		if (idx * 3 + 1 > game->level) {
			btn1->setColor(Color3B(100, 100, 100));
			cell->getChildByTag(201)->setVisible(true);
		}
		else {
			btn1->setColor(Color3B(255, 255, 255));
			cell->getChildByTag(201)->setVisible(false);
		}

		if (idx * 3 + 2 > game->level) {
			btn2->setColor(Color3B(100, 100, 100));
			cell->getChildByTag(202)->setVisible(true);
		}
		else {
			btn2->setColor(Color3B(255, 255, 255));
			cell->getChildByTag(202)->setVisible(false);
		}

		if (idx * 3 + 3 > game->level) {
			btn3->setColor(Color3B(100, 100, 100));
			cell->getChildByTag(203)->setVisible(true);
		}
		else {
			btn3->setColor(Color3B(255, 255, 255));
			cell->getChildByTag(203)->setVisible(false);
		}

		if(idx == 6)
		{
			btn3->setVisible(false);
			lb->setVisible(false);
			cell->getChildByTag(203)->setVisible(false);
		}
		else
		{
			btn3->setVisible(true);
			lb->setVisible(true);
		}
		
//	}


	return cell;
}
ssize_t TableListPostureEgg::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return 20 / 3 + 1;
}


void TableListPostureEgg::resultCallback( CCObject* pSender )
{

	CCMenuItemImage *image = static_cast<CCMenuItemImage*>(pSender);
	GUIManager::getInstance().removeAllGui();
	if (image->getTag() > game->level) {
		GUIManager::getInstance().guiDialog.showGUI("You need to complete the previous level");
		return;
	}
	GUIManager::getInstance().guiEgg.showGui(image->getTag());
	JNIUtils::sendEvent("choose_level", GameUtility::toString(image->getTag()).c_str());
}


void TableListPostureEgg::selectLevel(int level)
{
	if (level > game->level) {
		GUIManager::getInstance().guiDialog.showGUI("You need to complete the previous level");
		return;
	}
	GUIManager::getInstance().removeAllGui();
	GUIManager::getInstance().guiEgg.showGui(level);
	JNIUtils::sendEvent("choose_level", GameUtility::toString(level).c_str());
}
