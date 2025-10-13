#ifndef TopCell_H
#define TopCell_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIText.h"
#include "2d/CCSprite.h"
#include "../GameClient.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
class TopCell : public TableViewCell
{
public:
	TopCell();
	~TopCell(void);
	float widthRow;
	float heightRow;
	bool isMe;
	Scale9Sprite* slot;
	Text* labelStt;
	Sprite* avatar;
	Sprite* imgRank;
	Sprite* borderAvatar;
	Text* labelName;
	Text* labelScore;
	void setInfo(TopData data);
};
#endif

