#include "TopCell.h"
#include "ui/UIText.h"
#include "../Utility/GameUtility.h"
#include "Engine/GlobalVar.h"

TopCell::TopCell() :TableViewCell()
{
	string resource ="Board/table/top/bgCell.png";
	slot = Scale9Sprite::create(resource);
	widthRow = slot->getContentSize().width;
	heightRow = slot->getContentSize().height;
	//slot->setContentSize(CCSize(widthRow, heightRow));
	this->addChild(slot);
	slot->setPosition(widthRow * 0.5f, heightRow * 0.5f);
	slot->setTag(1);

	labelStt = Text::create("1", "fonts/tahomabd.ttf", 16);
	labelStt->enableOutline(ccc4(132, 34, 13, 255), 1);
	labelStt->setTextColor(ccc4(150, 150, 150, 255));
	labelStt->enableOutline(ccc4(137, 47, 43, 255), 2);
	labelStt->setTextColor(ccc4(241, 200, 200, 255));
	labelStt->setTextHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(labelStt);
	labelStt->setTag(2);
	labelStt->setAnchorPoint(ccp(0.5, 0.5f));
	labelStt->setPosition(ccp(widthRow * 0.07f, slot->getPositionY()));

	imgRank = Sprite::create("Board/table/top/rank1.png");
	this->addChild(imgRank);
	imgRank->setScale(0.7f);
	imgRank->setPosition(ccp(labelStt->getPositionX(), slot->getPositionY()));

	avatar = Sprite::create("Board/table/avatar/avatar_0.png");
	this->addChild(avatar);
	avatar->setScale(0.5f);
	avatar->setPosition(ccp(widthRow * 0.22f, slot->getPositionY()));
	avatar->setTag(3);

	borderAvatar = Sprite::create("Board/table/avatar/level0.png");
	this->addChild(borderAvatar);
	borderAvatar->setScale(0.5f);
	borderAvatar->setPosition(avatar->getPosition());
	borderAvatar->setTag(30);

	labelName = Text::create("Player", "fonts/tahomabd.ttf", 16);
	labelName->enableOutline(ccc4(132, 34, 13, 255), 1);
	labelName->enableOutline(ccc4(137, 47, 43, 255), 2);
	labelName->setTextColor(ccc4(241, 200, 200, 255));
	labelName->setTextHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(labelName);
	labelName->setTag(4);
	labelName->setAnchorPoint(ccp(0, 0.5f));
	labelName->setPosition(ccp(widthRow * 0.34f, slot->getPositionY()));

	labelScore = Text::create("100", "fonts/tahomabd.ttf", 16);
	labelScore->enableOutline(ccc4(137, 47, 43, 255), 2);
	labelScore->setTextColor(ccc4(241, 200, 200, 255));
	this->addChild(labelScore);
	labelScore->setTag(5);
	labelScore->setTextHorizontalAlignment(TextHAlignment::LEFT);
	labelScore->setAnchorPoint(ccp(0, 0.5f));
	labelScore->setPosition(ccp(widthRow * 0.75f, slot->getPositionY()));
}

TopCell::~TopCell(void)
{
}

void TopCell::setInfo(TopData data)
{
	int idx = data.index;
	labelStt->setText(to_string(idx));
	avatar->setTexture("Board/table/avatar/avatar_" + to_string((int)(CCRANDOM_0_1() * 3.9999)) + ".png");
	int index = 20 - idx;
	index = index >= 0 ? index : 0;
	//index = (int)(CCRANDOM_0_1() * 14.9999);
	borderAvatar->setTexture("Board/table/avatar/level" + to_string(index) + ".png");

	string name = data.name.compare("") == 0 ? "No Name" : data.name;
	labelName->setText(GameUtility::standardizeString(name, 20));
	if (data.typeTop == TOP_TIME) {
		string s = GameUtility::convertTime(data.score);
		labelScore->setText(s);
	}
	else {
		labelScore->setText(GameUtility::standardizeNumber(data.score));
	}
	
	if (idx <= 3) {
		imgRank->setVisible(true);
		labelStt->setVisible(false);
		imgRank->setTexture("Board/table/top/rank" + to_string(idx) + ".png");
		slot->setTexture("Board/table/top/bgCell" + to_string(idx) + ".png");
	}
	else {
		imgRank->setVisible(false);
		labelStt->setVisible(true);
		if (data.id.compare(game->deviceId) == 0) {
			slot->setTexture("Board/table/top/bgCell1.png");
		}
		else {
			slot->setTexture("Board/table/top/bgCell.png");
		}
	}
	//string resource = (isMe) ? "Board/table/top/bgRank1.png" : "Board/table/top/bgRank.png";
}

