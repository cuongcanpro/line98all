#include "BubbleText.h"


BubbleText::BubbleText()
{
	bg = Scale9Sprite::create("480_800/gameBubble/bgDialog.png");
	this->addChild(bg);
// 	
// 	bg = CCSprite::create("480_800/gameBubble/bgDark.png");
// 	this->addChild(bg);

//	CCScale9Sprite *bgLogin = CCScale9Sprite::create("480_800/bgClockGame.png");
	//bgLogin->setContentSize(ccp(size.width * 0.96f, heightInput * 5));

	text = LabelBM::create("Text", FONT_SMALL_NORMAL_TYPE);
	//text->setAnchorPoint(ccp(0.5f, 0.75f));
	this->addChild(text);
	text->setWidth(CCDirector::sharedDirector()->getWinSize().width * 0.4);
	text->setLineBreakWithoutSpace(false);
	setCascadeOpacityEnabled(true);
}


BubbleText::~BubbleText()
{

}

void BubbleText::setText(const char* s)
{
	text->setPos(0, 0);
	text->setText(s);
	float scale = (text->getContentSize().width + 20) / bg->getContentSize().width;
	bg->setScaleX(scale);
	scale = (text->getContentSize().height + 10) / bg->getContentSize().height;
	bg->setScaleY(scale);
	setContentSize(CCSizeMake(bg->getContentSize().width * bg->getScaleX(), bg->getContentSize().height * bg->getScaleY()));
	
}

