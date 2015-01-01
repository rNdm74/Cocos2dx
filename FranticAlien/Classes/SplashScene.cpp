#include "SplashScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
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
    
    auto label = LabelTTF::create("Splash", "Marker Felt", 80);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 2) + (label->getContentSize().height) / 2));
    
    label->setOpacity(0);

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // fade in / out action
    
    
    Vector<cocos2d::FiniteTimeAction*> fadeActions(3);
    
    fadeActions.insert(0, CallFunc::create(CC_CALLBACK_0(SplashScene::loadMenuScene, this)));
    fadeActions.insert(0, FadeOut::create(0.5));
    fadeActions.insert(0, FadeIn::create(0.5));
    
    
    label->runAction(Sequence::create(fadeActions));
    
    return true;
}

void SplashScene::loadMenuScene()
{
    //CCLog("%s", "next scene");
    
    auto menuScene = MenuScene::createScene();
    Director::getInstance()->replaceScene(menuScene);
}

void SplashScene::menuCloseCallback(Ref* pSender)
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
