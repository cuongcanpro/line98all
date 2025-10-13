#ifndef _CSCALE_SPRITE_H_
#define _CSCALE_SPRITE_H_
#include "cocos2d.h"
#include "../Utility/ScreenUtils.h"

USING_NS_CC;

class CScaleSprite:
public CCSprite{
public:
	///static CScaleSprite* create();
	static CScaleSprite* create(const char *pszFileName, bool frame = false);
	float getWidth();
	float getHeight();
	virtual void setScale(float scale);
	virtual void setScaleX(float scale);
	virtual void setScaleY(float scale);
	virtual float getScaleX();
	virtual float getScaleY();
	virtual float getScale();
private:
	CCSize newSize;
	void updateSize();
};
#endif
