#include "GameplayFinishedScene.h"
#include "AppGlobal.h"
#include "GameplayScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* GameplayFinishedScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameplayFinishedScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameplayFinishedScene::init()
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
    auto label = LabelTTF::create(AppGlobal::getInstance()->getActiveLevel(), "Arial", 80);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 2) + (label->getContentSize().height) / 2));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    FiniteTimeAction* waitAction = DelayTime::create(2);
    FiniteTimeAction* waitFinished = CallFunc::create(CC_CALLBACK_0(GameplayFinishedScene::Finished, this));    
    this->runAction(Sequence::createWithTwoActions(waitAction, waitFinished));
    
    return true;
}

void GameplayFinishedScene::Pause(Ref* sender)
{
    Scene* menuScene = MenuScene::createScene();
    
    Director::getInstance()->pushScene(menuScene);
}

void GameplayFinishedScene::Finished()
{
    // Increase level
    AppGlobal::getInstance()->ActiveLevel++;
    
    auto gameplayScene = GameplayScene::createScene();
    Director::getInstance()->replaceScene(gameplayScene);
}

void GameplayFinishedScene::menuCloseCallback(Ref* pSender)
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
