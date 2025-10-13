#include "GUILoadingAds.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../GUIManager.h"
#include "../Utility/JNIUtils.h"
#include "../../Engine/GlobalVar.h"
GUILoadingAds::GUILoadingAds(void) : BaseGUI()
{
	BaseGUI();
}


GUILoadingAds::~GUILoadingAds(void)
{
}

void GUILoadingAds::initGUI(){
    BaseGUI::initGUI();
	CCSize size = Director::getInstance()->getOpenGLView()->getVisibleSize();
	GameImage* background = addImage("blackLayer.png");
	background->setOpacity(200);
	background->setWidth(size.width);
	background->setHeight(size.height);
	background->setPos(size.width * 0.5f, size.height * 0.5f);

	loading = this->addImage("iconLoading.png");
	loading->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 359)));
	loading->setPosition(size.width * 0.5f, size.height * 0.55f);

	Text* lbBestScore = Text::create("Please Wait....", "fonts/tahomabd.ttf", 25);
	lbBestScore->setTextHorizontalAlignment(TextHAlignment::CENTER);
	lbBestScore->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(lbBestScore);
	lbBestScore->setPosition(Vec2(size.width * 0.5, loading->getPositionY() - 50));
}

void GUILoadingAds::autoHideGUI()
{
	if (isVisible())
		GUIManager::getInstance().removeFromListGui();
}

void GUILoadingAds::showAds(bool needLoad)
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
	loading->cleanup();
	loading->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 359)));
    if (game->timeNoAds < 100) {
        runAction(
            Sequence::create(
                DelayTime::create(1.0),
                CCCallFunc::create(this, callfunc_selector(GUILoadingAds::autoHideGUI)),
                NULL
            )
        );
        return;
    }
        
	if (needLoad) {
		//JNIUtils::loadShowAdsInter();
		runAction(
			Sequence::create(
				DelayTime::create(5.0),
				CCCallFunc::create(this, callfunc_selector(GUILoadingAds::callbackShowAds)),
				NULL
			)
		);
	}
	else {
		runAction(
			Sequence::create(
				DelayTime::create(1.0),
				CCCallFunc::create(this, callfunc_selector(GUILoadingAds::callbackShowAds)),
				NULL
			)
		);
	}
}

void GUILoadingAds::callbackShowAds()
{
    JNIUtils::showAdsFull();
	runAction(
		Sequence::create(
			DelayTime::create(2.0),
			CCCallFunc::create(this, callfunc_selector(GUILoadingAds::autoHideGUI)),
			NULL
		)
	);
}

void GUILoadingAds::showGUI( CCNode* parent /* = NULL */, bool hasFog /* = true */ )
{
	BaseGUI::showGUI();
	setVisible(true);
	GUIManager::getInstance().addToListGui(this);
	
	loading->cleanup();
	loading->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 359)));
	runAction(
		Sequence::create(
			DelayTime::create(5.0),
			CCCallFunc::create(this, callfunc_selector(GUILoadingAds::autoHideGUI)),
			NULL
		)
	);
}
