#pragma once
#ifndef BubbleText_h__
#define BubbleText_h__

#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
class BubbleText : public CCNodeRGBA
{
public:
	BubbleText();
	~BubbleText();
	Scale9Sprite* bg;
	LabelBM* text;
	void setText(const char* s);

};
#endif // BubbleText_h__

