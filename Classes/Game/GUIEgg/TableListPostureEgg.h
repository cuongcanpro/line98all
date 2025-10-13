#ifndef TABLE_LIST_GIFT_EGG_H
#define TABLE_LIST_GIFT_EGG_H

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
class TableListPostureEgg : public TableViewDataSource, public TableViewDelegate, public Ref
{
public:
	TableListPostureEgg(void);
	~TableListPostureEgg(void);

	
	vector <CCMenuItemImage*> arrayResult;

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	vector<Button*> arrayButton;
	void resultCallback(CCObject* pSender);
	void selectLevel(int level);
};
#endif

