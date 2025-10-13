#ifndef ParticleEffect_h__
#define ParticleEffect_h__

#include "cocos2d.h"

#include <string>
using namespace cocos2d;

using namespace std;

class ParticleEffect
{
public:
	ParticleEffect(void);
	~ParticleEffect(void);

	void create(string particlePath, CCNode* parent = NULL);

public:
	CCParticleSystem* particle;
};
#endif // ParticleEffect_h__

