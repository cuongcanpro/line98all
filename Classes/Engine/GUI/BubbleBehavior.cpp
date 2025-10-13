#include "BubbleBehavior.h"
//#include "Sound/CSound.h"

BubbleBehavior::BubbleBehavior(void)
{
}


BubbleBehavior::~BubbleBehavior(void)
{
}

void BubbleBehavior::onTouchBegan(CCTouch*touch, BaseButton* touchButton)
{
	if(!touchButton->isEnable()) return;

	touchButton->normalImage->addEffectScaleSmaler();
}

void BubbleBehavior::onTouchEnded( CCTouch* touch, BaseButton* releaseButton )
{
	if(!releaseButton->isEnable()) return;

	releaseButton->normalImage->addEffectBubble();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
	//CSound::shared()->playEffectById(touchPoint,SOUND_FUNC_CLICK_BUTTON);
}
