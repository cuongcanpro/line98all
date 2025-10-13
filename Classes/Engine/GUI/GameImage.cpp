#include "GameImage.h"
#include "../GlobalVar.h"

using namespace cocos2d;



GameImage::GameImage(void)
{ 
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
}


GameImage::~GameImage(void)
{
	clear();
}

GameImage::GameImage(const char* imageName, bool frame)
{
	_img = CScaleSprite::create(imageName, frame);
	this->addChild(_img);
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
}

GameImage::GameImage(CCNode* parent, const char * imageName, float x, float y) :CCNode()
{
	_img = CScaleSprite::create(imageName);
	this->addChild(_img);

	if(parent)
	{
		parent->addChild(this);
	}
	if(imageName==NULL)
	{
		autorelease();
	}
	setPos(x,y);
	_scaleRootX=1.0f;
	_scaleRootY=1.0f;
	_enable=true;
}

void GameImage::setPos(float x,float y)
{
	setPosition(ccp(x,y));
}

void GameImage::setVisible(bool visible)
{
	CCNode::setVisible(visible);
	_img->setVisible(visible);
}
bool GameImage::getVisible()
{
	return _img->isVisible()&&isVisible();
}

float GameImage::getWidth()
{
	int asd = _img->getWidth();
	int asdd = _img->getScale();
	return _img->getWidth()*_scaleRootX;
}

void GameImage::setWidth(float widthValue)
{
	float scale = widthValue/getWidth();
	this->setScaleX(scale);
}

void GameImage::setHeight(float heightValue)
{
	float scale = heightValue/getHeight();
	this->setScaleY(scale);
}

float GameImage::getHeight()
{
	return _img->getHeight()*_scaleRootY;
}

CCRect GameImage::rect()	
{
	CCSize s = CCSizeMake(_img->getWidth(),_img->getHeight());
	CCPoint p;
	p=_img->getPosition();
	return CCRectMake(p.x-s.width*_img->getAnchorPoint().x,p.y-s.height*_img->getAnchorPoint().y, s.width, s.height);
};

bool GameImage::containsTouchLocation(CCTouch* touch)
{
	CCPoint pos=convertTouchToNodeSpaceAR(touch);
	return  rect().containsPoint(pos);
}

void GameImage::setImage(const char*namImg, bool isFrame)
{
	removeAllChildren();
	_img = CScaleSprite::create(namImg, isFrame);
	addChild(_img);
	//_img->setTexture(ResMgr::getTexture2D(namImg));
}

void GameImage::setOnlyImage( const char* namImg)
{
	removeChild(_img);
	_img = CScaleSprite::create(namImg);
	addChild(_img);
}
void GameImage::registerTouch()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCNode::onEnter();
}

void GameImage::clear()
{
	if (this->getParent())
	{
		_img->stopAllActions();
		onExit();
		this->removeAllChildren();
		this->removeFromParentAndCleanup(true);
	}
}


void GameImage::addMoveEffect(float x, float y)
{
	// TODO: Add movement time based on speed
	CCMoveTo *actionMove = CCMoveTo::create(0.2f, CCPoint(x, y));
	stopAllActions();
	this->runAction(actionMove);
}

void GameImage::setFlipX( bool flip )
{
	_img->setFlipX(flip);

}

void GameImage::setAnchorPointImage( const CCPoint &anchorPoint )
{
	_img->setAnchorPoint(anchorPoint);
}
const CCPoint& GameImage::getAnchorPointImage()
{
	return _img->getAnchorPoint();
}
void GameImage::removeTouch()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->removeDelegate(this);
}

void GameImage::addEffectScaleSmaler()
{
	// Actions presets
	float scX=0.9f*_scaleRootX;
	float scY=0.9f*_scaleRootY;
	CCActionInterval*  actionBy = CCScaleBy::create(0.1f,scX , scY);


	// TODO: restore original scale
	this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction(actionBy);

}

void GameImage::addEffectScaleLager()
{
	// Actions presets
	CCActionInterval*  actionBy = CCScaleBy::create(0.1f,1.15f ,1.15f);


	// TODO: restore original scale
	//this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction( actionBy);

}

void GameImage::addEffectSweep()
{
	// Actions presets
	CCActionInterval*  actionRotate1 = CCRotateBy::create(0.3f,-12.f);
	CCActionInterval*  actionRotate2 = CCRotateBy::create(0.3f,12.f);
	CCActionInterval* move_ease_in = CCEaseBounceIn::create((CCActionInterval*)(actionRotate1->copy()->autorelease()) );
	CCActionInterval* move_ease_in_back = move_ease_in->reverse();
	CCDelayTime *delay = CCDelayTime::create(0.1f);

	CCActionInterval* move_ease_out = CCEaseBounceOut::create((CCActionInterval*)(actionRotate2->copy()->autorelease()) );
	CCActionInterval* move_ease_out_back = move_ease_out->reverse();


	// TODO: restore original scale
//	this->stopAllActions();
	this->setRotation(0);
	//this->setScale(_scaleRoot);

	// Run action
	this->runAction( CCSequence::create(actionRotate1,delay,actionRotate1->reverse(),actionRotate2,delay,actionRotate2->reverse(), NULL));
}

void GameImage::setScaleRoot( float scale )
{
	_scaleRootX=scale;
	_scaleRootY = scale;

}

void GameImage::setScaleRootX( float scaleX)
{
	_scaleRootX=scaleX;
}

void GameImage::setScaleRootY( float scaleY)
{
	_scaleRootY=scaleY;
}

CScaleSprite* GameImage::getSprite()
{
	return _img;
}
void GameImage::addEffScaleRoot()
{
	//this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);
}

void GameImage::addEffectBubble()
{
	// Actions presets
	CCActionInterval*  actionBy = CCScaleBy::create(0.1f, 1.17f*_scaleRootX, 1.17f*_scaleRootY);


	// TODO: restore original scale
	this->stopAllActions();
	this->setScaleX(_scaleRootX);
	this->setScaleY(_scaleRootY);

	// Run action
	this->runAction( CCSequence::create(actionBy, actionBy->reverse(), NULL));
}

void GameImage::setEnable(bool enable)
{
	_enable=enable;
	if(enable)
	{
 #if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
 		_img->setColor(ccc3(255, 255, 255));
 #else
		_img->setColor(ccc3(255, 255, 255));
	//	_img->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kShaderNormal));
		//_img
#endif
	}
	else
	{
		setDisable();
	}
}

void GameImage::setDisable()
{
 #if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
 	_img->setColor(ccc3(100, 100, 100));
 #else
	_img->setColor(ccc3(100, 100, 100));
	//_img->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kShaderGrayProgram));
#endif
	_enable=false;
}
void GameImage::addEffFadeIn(float time, SEL_CallFuncN callBack )
{
	
}


void GameImage::addEffFadeOut( float time,float delay,SEL_CallFuncN callBack )
{
	_img->stopAllActions();
	CCActionInterval* actionFade=CCFadeOut::create(time);
	CCDelayTime *delayAction = CCDelayTime::create(delay);
	CCCallFuncN* callFunc=CCCallFuncN::create(_img, callBack);

	CCFiniteTimeAction*  action = CCSequence::create(
		delayAction,
		actionFade,
		callFunc,
		NULL);
	_img->runAction(action);
}

void GameImage::setOpacity( GLubyte alpha )
{
	_img->setOpacity(alpha);
}

void GameImage::addLabel( LabelBM* text )
{
	_img->addChild(text);
}

bool GameImage::isEnable()
{
	return _enable;

}

void GameImage::addEffTint()
{
	// Create actions
	CCActionInterval* action1		= CCTintBy::create(0.75f, -150, -150, -150);
	CCActionInterval* action1Back	= action1->reverse();
	CCActionInterval* actionScale=CCScaleTo::create(0.75f,0.95f,0.95f);
	CCActionInterval* actionScaleBack=CCScaleTo::create(0.75f,1.1f,1.1f);
	CCActionInterval* action11=CCSequence::create(action1, 
		action1Back, 
		NULL );
	CCActionInterval* action21=CCSequence::create(actionScale, 
		actionScaleBack, 
		NULL );

	CCFiniteTimeAction* actionSpaw=CCSpawn::create(
			action11,
			action21,
			NULL);
	

	CCRepeatForever *repeatAction = CCRepeatForever::create((CCActionInterval*)action21);

	// Run action
	_img->stopAllActions();
	_img->setColor(Color3B::WHITE);
	_img->runAction( repeatAction);
}

void GameImage::addEffArrowVertical()
{
	

}

void GameImage::removeEffTint()
{
	if(_img)
	{
		_img->stopAllActions();
		_img->setScale(1);
	}

}

void GameImage::setLighter( bool light )
{
	if(light)
	{
		_img->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kShaderLighter));

	}
	else
	{
		_img->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kShaderNormal));
	}

}

void GameImage::setColor( ccColor3B color )
{
	_img->setColor(color);
}

void GameImage::setImgContentSize(CCSize size)
{
	_img->setContentSize(size);
}

CCSprite* GameImage::getImg()
{
	return _img;
}

float GameImage::getRealWidth()
{
	return _img->getWidth() * getScaleX();
}

float GameImage::getRealHeight()
{
	return _img->getHeight() * getScaleY();
}