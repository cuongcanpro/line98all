#pragma once
#ifndef CellBomb_h__
#define CellBomb_h__
#include "string"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIImageView.h"
#include "../Logic/CellState.h"

using namespace std;
using namespace cocos2d;
using namespace ui;


class CellBomb : public Node
{
public:
	CellBomb(void);
	~CellBomb(void);
	Scale9Sprite* bg;
	Scale9Sprite* bgMask;
	Sprite* iconBomb;
	Sprite* iconWrong;
	Sprite* lbNum;
	Sprite* icon;
	int numVibrate;
	CellDataState cellState;
	void setState(CellDataState state, int num = 0, float delayTime = 0);
	void showIconWrong();
	void hideMask(float delay);
	void showMask(float delay);
	void effectVibrate();
	void effectNoti();
	void effectNewGame(float delay);
};
#endif // Cell_h__

