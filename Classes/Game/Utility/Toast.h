#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../Engine/GUI/LabelBM.h"
#include "../../Engine/Utility/LocalizedString.h"

USING_NS_CC;
USING_NS_CC_EXT;
class Toast : public CCNode
{
public:
	Toast(void);
	~Toast(void);
	CREATE_FUNC(Toast);
	virtual bool init();
	static Toast *create(const char* _lb);
	static void makeToast(float duration,const char* msg);
	static void clearToast();
	void setMsg(const char* msg);
protected:
	ui::Scale9Sprite *_9patch;
	CCLabelTTF *_label;
	void callbackFree(CCNode *sender);
	LabelBM *_lbBM;
};

