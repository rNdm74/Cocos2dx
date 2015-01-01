#include "GameplayScene.h"
#include "GameplayFinishedScene.h"
#include "MenuScene.h"
#include "Entity.h"
#include "AppGlobal.h"
#include "Player.h"

enum
{
    kTagNode,
    kTagPlayer,
    kTagStartPosition
};

USING_NS_CC;


Scene* GameplayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GameplayScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

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

    // Mouse & Touch input
    //auto allAtOnceListener = EventListenerTouchAllAtOnce::create();
	//allAtOnceListener->onTouchesMoved = CC_CALLBACK_2(GameplayScene::onTouchesMoved, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(allAtOnceListener, this);

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
    
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameplayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // create and initialize a menu
    auto menu_item_1 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameplayScene::Pause, this));
    auto menu_item_2 = MenuItemFont::create("-->", CC_CALLBACK_1(GameplayScene::GameplaySceneFinished, this));
    
    Menu* menu = Menu::create(menu_item_1, menu_item_2,NULL);
    menu->setPositionX(100);
    menu->setPositionY(this->getContentSize().height - 10);
	this->addChild(menu, 100);

    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	    
	tilemap = TileMap::create("tiles_spritsheet.tmx");
	this->addChild(tilemap);
		    
	// Player
	p = Player::createPlayerWithFilename("alienBeige_stand.png");
	p->setTag(kTagPlayer);
	p->setPosition(center);
	p->Stand();
	this->addChild(p, 2);

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
	//direction.x = -1;

	tilemap->updatePosition();

	p->Update(delta);

	float x = tilemap->getPositionX();

	x += 400 * delta  * direction.x;

	tilemap->setPositionX(x);
}

void GameplayScene::actionFinished()
{
	p->Stand();
}

bool GameplayScene::onContactBegin(PhysicsContact &contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((1 == a->getCollisionBitmask()) && (2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask()) && (1 == b->getCollisionBitmask()))
	{
		//log("contact");

		//a->setGravityEnable(false);
		//b->setGravityEnable(false);
	}

	return true;
}

bool GameplayScene::onTouchBegan(Touch* touch, Event  *event)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 playerPoint = p->getPosition();
	Rect rect = p->getBoundingBox();

	if (p->IsSelected == false && rect.containsPoint(touchPoint))
	{
		p->showMenu();
	}
	else if (p->IsSelected == true && rect.containsPoint(touchPoint))
	{
		p->hideMenu();
	}
	else if (p->IsSelected == false && rect.containsPoint(touchPoint) == false)
	{
		direction.x = (touchPoint.x > playerPoint.x) ? -1 : 1;
		p->Walk(touchPoint);
	}
	
	return true;
}

void GameplayScene::onTouchMoved(Touch* touch, Event  *event)
{
}

void GameplayScene::onTouchEnded(Touch* touch, Event  *event)
{
	direction = Vec2::ZERO;

	if (p->IsSelected == false)
	{
		p->Stand();
	}
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
