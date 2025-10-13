#ifndef BubbleBehavior_h__
#define BubbleBehavior_h__

#include "BaseBehavior.h"

class BubbleBehavior :
	public BaseBehavior
{
public:
	BubbleBehavior(void);
	~BubbleBehavior(void);

public:
	void onTouchBegan(CCTouch*touch, BaseButton* touchButton);
	void onTouchEnded(CCTouch* touch, BaseButton* releaseButton);
};
#endif // BubbleBehavior_h__

