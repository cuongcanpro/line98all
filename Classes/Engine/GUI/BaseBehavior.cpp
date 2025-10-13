#include "BaseBehavior.h"


BaseBehavior::BaseBehavior(void)
{
	_idBehavior=0;
}


BaseBehavior::~BaseBehavior(void)
{
}

void BaseBehavior::onTouchBegan(CCTouch*touch, BaseButton* touchButton)
{

}

void BaseBehavior::onTouchMoved(CCTouch*touch, BaseButton* dragButton)
{

}

void BaseBehavior::onTouchEnded(CCTouch*touch, BaseButton* releaseButton)
{

}
void BaseBehavior::onCanceled (BaseButton* button)
{

}
void BaseBehavior::onAdd(BaseButton* button)
{

}

void BaseBehavior::setVisible( bool visible )
{

}

int BaseBehavior::getId()
{
	return _idBehavior;
}

void BaseBehavior::setId( int id )
{
	_idBehavior=id;

}

void BaseBehavior::updatePos( BaseButton* ownerBtn )
{

}
