#include "AppGlobal.h"
#include "Constants.h"
#include "GameplayScene.h"
#include "GameplayFinishedScene.h"
#include "MenuScene.h"
#include "World.h"

Scene* GameplayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	
    // 'layer' is an autorelease object
    auto layer = GameplayScene::create();
	layer->setTag(KTagSceneLayer);

	// add cursor
	AppGlobal::getInstance()->addCursor(*layer);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameplayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	    
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameplayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameplayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameplayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // Keyboard input
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameplayScene::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(GameplayScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    

    // create and initialize a menu
    auto menu_item_1 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameplayScene::Pause, this));
    auto menu_item_2 = MenuItemFont::create("-->", CC_CALLBACK_1(GameplayScene::GameplaySceneFinished, this));
    
    Menu* menu = Menu::create(menu_item_1, menu_item_2,NULL);
    menu->setPositionX(100);
    menu->setPositionY(this->getContentSize().height - 10);
	this->addChild(menu, 100);

	world = World::create();
	this->addChild(world);
	    
	//
    this->scheduleUpdateWithPriority(42);   
    
    return true;
}

void GameplayScene::Pause(Ref* sender)
{
	Scene* menuScene = MenuScene::createScene();
	Director::getInstance()->pushScene(menuScene);
}

void GameplayScene::GameplaySceneFinished(Ref* sender)
{
	auto gameplayFinishedScene = GameplayFinishedScene::createScene();
	Director::getInstance()->replaceScene(gameplayFinishedScene);
}

void GameplayScene::update(float delta)
{
	world->update(delta);
}

void GameplayScene::actionFinished()
{	
}

bool GameplayScene::onContactBegin(PhysicsContact &contact)
{
	return true;
}

bool GameplayScene::onTouchBegan(Touch* touch, Event  *event)
{
	return true;
}

void GameplayScene::onTouchMoved(Touch* touch, Event  *event)
{
}

void GameplayScene::onTouchEnded(Touch* touch, Event  *event)
{
}

void GameplayScene::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
}

void GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{        
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Scene* menuScene = MenuScene::createScene();
        Director::getInstance()->pushScene(menuScene);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_SHIFT)
    {       
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {       
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_W)
    {       
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_S)
    {        
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_A)
    {       
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_D)
    { 
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_Q)
    {       
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_E)
    {        
    }
}

void GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{	
}

void GameplayScene::menuCloseCallback(Ref* pSender)
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
