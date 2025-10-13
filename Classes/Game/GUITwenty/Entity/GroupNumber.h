#ifndef _GroupNumber_h__
#define _GroupNumber_h__
#include <cocos2d.h>
#include "Engine/GUI/GameImage.h"
#include "Engine/GUI/LabelBM.h"
using namespace cocos2d;
class GroupNumber : public CCNode
{
public:

	GroupNumber(void);
	~GroupNumber(void);
	GameImage* ball;
	LabelBM* label;
	int number;
	void setNumber(int number);
	void increaseNumber();
	void callback1();
	void callback2();
};
#endif
