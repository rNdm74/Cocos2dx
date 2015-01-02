#include "MenuScene.h"
#include "AppGlobal.h"
#include "LoadingScene.h"
#include "SettingsScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create and initialize a menu items
    auto menu_item_1 = MenuItemFont::create("Continue", CC_CALLBACK_1(MenuScene::Continue, this));
    auto menu_item_2 = MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::Play, this));
    auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(MenuScene::Settings, this));
    auto menu_item_4 = MenuItemFont::create("Quit", CC_CALLBACK_1(MenuScene::Quit, this));
    
    
    
    if(AppGlobal::getInstance()->IsGameSceneRunning)
    {
        menu = Menu::create(menu_item_1, menu_item_3, menu_item_4, NULL);
    }
    else
    {
        menu = Menu::create(menu_item_2, menu_item_3, menu_item_4, NULL);

    }
    
    menu->alignItemsVerticallyWithPadding(25.0f);
    this->addChild(menu);
    
    //auto mouseListener = EventListenerMouse::create();
    //mouseListener->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
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

    
    
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    return true;
}

void MenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    //log("Key with keycode %d pressed", keyCode);
    //int key = (int)EventKeyboard::KeyCode::KEY_KP_ENTER;
    //log("Enter pressed %i", key);
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        if(AppGlobal::getInstance()->IsGameSceneRunning)
        {
            Director::getInstance()->popScene();
        }
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_RETURN ||
            keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER ||
            keyCode == EventKeyboard::KeyCode::KEY_ENTER)
    {
        
        if(AppGlobal::getInstance()->IsGameSceneRunning)
        {
            Director::getInstance()->popScene();
        }
        else
        {
            auto loadingScene = LoadingScene::createScene();
            Director::getInstance()->pushScene(loadingScene);
        }
    }
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
}

void MenuScene::onMouseEnter(Event* event)
{
}

void MenuScene::onMouseMove(Event *event)
{
    //EventMouse* e = (EventMouse*)event;
}

void MenuScene::Continue(Ref* sender)
{
    //auto loadingScene = LoadingScene::createScene();
    //Director::getInstance()->pushScene(loadingScene);
    
    Director::getInstance()->popScene();
}

void MenuScene::Play(Ref* sender)
{
    auto loadingScene = LoadingScene::createScene();
    Director::getInstance()->pushScene(loadingScene);
}

void MenuScene::Settings(Ref* sender)
{
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->pushScene(settingsScene);
}

void MenuScene::Quit(Ref* sender)
{
    if(AppGlobal::getInstance()->IsGameSceneRunning)
    {
        AppGlobal::getInstance()->IsGameSceneRunning = false;
        
        Director::getInstance()->popToRootScene();
    }
    else
    {
        exit(0);
    }
}


void MenuScene::menuCloseCallback(Ref* pSender)
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
