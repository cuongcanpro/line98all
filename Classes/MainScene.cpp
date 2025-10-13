#include "MainScene.h"
#include "Engine/GlobalVar.h"

using namespace cocos2d;

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 104);
    scene->retain();

	// Call Game Client init
	mainScene = scene;
	if (game)
		game->init();

    // return the scene
	
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	schedule(schedule_selector(MainScene::update),0);

	return true;
}

void MainScene::update(float delta)
{
	CCObject *object = NULL;
	game->update((delta));

}
		
