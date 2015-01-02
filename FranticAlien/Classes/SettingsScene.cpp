#include "SettingsScene.h"


USING_NS_CC;

Scene* SettingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create and initialize a menu
    auto menu_item_1 = MenuItemFont::create("Back", CC_CALLBACK_1(SettingsScene::Back, this));
    
    Menu* menu = Menu::create(menu_item_1, NULL);
    menu->alignItemsHorizontally();
    this->addChild(menu);
    
    auto tap = Sprite::create("tap.png");
    this->addChild(tap, 999);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](cocos2d::Event* event){
        
        // Cast Event to EventMouse for position details like above
        auto cursor = static_cast<EventMouse*>(event);
        
        auto pos = Vec2(cursor->getCursorX(), cursor->getCursorY());
        
        //log("x: %f, y:%f", pos.x, pos.y);
        
        tap->setPosition(pos);
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    
    
    return true;
}

void SettingsScene::Back(Ref* sender)
{
    Director::getInstance()->popScene();
}

void SettingsScene::menuCloseCallback(Ref* pSender)
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
