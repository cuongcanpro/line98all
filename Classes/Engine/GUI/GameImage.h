#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "cocos2d.h"
#include "LabelBM.h"
#include "CScaleSprite.h"

using namespace cocos2d;
class GameImage :public cocos2d::CCNode
{
public:
	CScaleSprite* _img;
	float _scaleRootX;
	float _scaleRootY;
	bool _enable;
public:
	GameImage(void);
	~GameImage(void);
	GameImage(const char* imageName, bool frame = false);
	GameImage(cocos2d::CCNode* parent,const char* imageName,float x,float y);
	int id;
	void setPos(float,float);
	virtual void setVisible(bool visible);
	bool getVisible();
	void setWidth(float width);
	void setHeight(float height);
	float getWidth();
	float getHeight();
	void setFlipX(bool flip);
	void setColor(ccColor3B color);

	//virtual void onEnter();
	//virtual void onExit();
	//virtual bool ccTouchBegan(CCTouch*touch,CCEvent* event);
	//virtual void ccTouchMoved(CCTouch*touch,CCEvent* event);
	//virtual void ccTouchEnded(CCTouch*touch,CCEvent* event);
	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);
	void setImage(const char*, bool isFrame = false);
	void setOnlyImage(const char*);
	void registerTouch();
	void removeTouch();
	void clear();
	void setAnchorPointImage(const CCPoint &anchorPoint);
	const CCPoint & getAnchorPointImage();
	void setScaleRoot(float scale);
	void setScaleRootX(float scaleX);
	void setScaleRootY(float scaleY);
	CScaleSprite* getSprite();

	float getRealWidth();
	float getRealHeight();
public:
	void addEffectScaleSmaler();
	void addEffectScaleLager();
	void addEffectBubble();
	void addMoveEffect(float x, float y);
	void addEffectSweep();
	void addEffScaleRoot();
	void addEffFadeIn(float time,SEL_CallFuncN callBack);
	void addEffFadeOut(float time,float delay,SEL_CallFuncN callBack);
	void addEffTint();
	void removeEffTint();
	void addEffArrowVertical();
public: 
	void setLighter(bool light);
	void setEnable(bool enable=true);
	void setDisable();
	void setOpacity(GLubyte	alpha);
	void addLabel(LabelBM* text);
	bool isEnable();
	void setImgContentSize(CCSize size);
	CCSprite* getImg();
};

#endif