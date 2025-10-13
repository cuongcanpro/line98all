#ifndef _BombEffect_h__
#define _BombEffect_h__
#include <cocos2d.h>
#include <Engine/GUI/ParticleEffect.h>

using namespace cocos2d;
class BombEffect : public Node
{
public:
	int max;
	BombEffect(void);
	~BombEffect(void);
    Sprite* imgBomb;
    ParticleEffect* effect;
    void showBomb(float timeDelay);
    void callbackShow();
};
#endif
