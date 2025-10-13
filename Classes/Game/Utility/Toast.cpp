#include "Toast.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"


Toast::Toast(void)
{
	
}


Toast::~Toast(void)
{
}

bool Toast::init(){
	if (!CCNode::init())
	{
		return false;
	}

	return true;
}

Toast *Toast::create(const char* _lb){
	Toast *_toast = Toast::create();
	CCSize size1 = Director::getInstance()->getOpenGLView()->getVisibleSize();
	_toast->_label = CCLabelTTF::create(_lb,"Arial", 20 * size1.width / 480);
	//_toast->_label->setDimensions(CCSize(100,300));

	CCSize size = _toast->_label->getContentSize();

	_toast->_9patch = Scale9Sprite::create(ScreenUtils::fileFull("9patch.png").c_str());
	_toast->_9patch->setPreferredSize(CCSizeMake(size.width + 16, size.height + 30));

	_toast->_9patch->setColor(Color3B::WHITE);
	_toast->addChild(_toast->_9patch);
	_toast->addChild(_toast->_label);

	_toast->setContentSize(CCSizeMake(size.width,size.height));
	return _toast;
}

void Toast::setMsg(const char* msg)
{
	_label->setString(msg);
	CCSize _size = _label->getContentSize();
	_9patch->setPreferredSize(CCSizeMake(_size.width + 16,_size.height +12));

	setContentSize(CCSizeMake(_size.width + 16,_size.height + 12));
}
void Toast::clearToast()
{
	Toast *_toast = (Toast *)layerMgr->getLayerByIndex(LAYER_CURSOR)->getChildByTag(11);
	if (_toast)
	{
		_toast->_9patch->stopAllActions();
		_toast->_label->stopAllActions();
		_toast->stopAllActions();
		_toast->setVisible(false);	
	}
}

void Toast::makeToast(float duration,const char* msg){

	Toast *_toast = (Toast *)layerMgr->getLayerByIndex(LAYER_CURSOR)->getChildByTag(11);

	if (_toast == NULL)
	{
		_toast = Toast::create(msg);
		layerMgr->getLayerByIndex(LAYER_CURSOR)->addChild(_toast);
		_toast->setTag(11);
	}
	else
	{
		_toast->_9patch->stopAllActions();
		_toast->_label->stopAllActions();
		_toast->stopAllActions();
		_toast->setMsg(msg);
		_toast->setVisible(false);	
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_toast->setPosition(winSize.width/2, winSize.height * 0.2f);
	_toast->_9patch->setOpacity(0);
	_toast->_label->setOpacity(0);
	_toast->_9patch->runAction(CCSequence::create(CCFadeIn::create(.15f),CCDelayTime::create(duration),CCFadeOut::create(.15f),NULL));
	_toast->_label->runAction(CCSequence::create(CCFadeIn::create(.15f),CCDelayTime::create(duration),CCFadeOut::create(.15f),NULL));
	_toast->runAction(CCSequence::create(CCShow::create(),CCDelayTime::create(duration + .3f),CCHide::create(),NULL));
	
}

void Toast::callbackFree(CCNode *sender){
	sender->removeFromParentAndCleanup(true);
}