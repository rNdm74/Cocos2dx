#include "AppGlobal.h"
#include "AppResources.h"
#include "Constants.h"
#include "GameplayScene.h"
#include "LoadingScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
	layer->setTag(KTagSceneLayer);

	// add cursor
	AppGlobal::getInstance()->addCursor(*layer);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create and initialize a label
    
    auto label = LabelTTF::create("Loading......", "Marker Felt", 80);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 2) + (label->getContentSize().height) / 2));

    // add the label as a child to this layer
    this->addChild(label, 1);

	AppResources::getInstance()->mainLoad();
    
    FiniteTimeAction* waitAction = DelayTime::create(0.1);
    FiniteTimeAction* waitFinished = CallFunc::create(CC_CALLBACK_0(LoadingScene::loadGameplayScene, this));
    
    this->runAction(Sequence::createWithTwoActions(waitAction, waitFinished));
    
    return true;
}

void LoadingScene::loadGameplayScene()
{
    AppGlobal::getInstance()->IsGameSceneRunning = true;
    auto gameplayScene = GameplayScene::createScene();
    Director::getInstance()->replaceScene(gameplayScene);
}

void LoadingScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
