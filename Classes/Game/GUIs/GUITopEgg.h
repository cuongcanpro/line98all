#pragma once
#include "TopCell.h"
#include "Engine/GUI/BaseGUI.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class GUITopEgg : public BaseGUI, public TableViewDataSource, public TableViewDelegate
{
public:
	GUITopEgg(void);
	~GUITopEgg(void);
public:
	void initGUI();
	void onBackKey();
	Button* btnTopWin, *btnTopGold, *btnTop, *btnPlay, *btnEdit;
	bool isOld;
	TableView* listTop;
	TopCell* myInfo;
	ui::Scale9Sprite *bg;
	ui::Scale9Sprite *bgList;
	Text* lbMode;
	Text* lbName;
	Text* lbScore;
	Text* lbRank;
	Text* lbEmpty;
	int currentTop;
	void onButtonRelease(int buttonID, CCTouch* touch);
	void showTop(int idTop);
	void reloadMyData();
	void reloadTopData();
	void insertDone();
	static std::string className;
	bool showNotice[5];
	Sprite* iconTop;
	Text* lbTop;
	LayerColor* layerDark;
	int highscore;

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
};

