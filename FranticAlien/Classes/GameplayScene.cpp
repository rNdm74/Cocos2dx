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
    
	//_sceneWorld->setGravity(Vec2(0, -9.8f));
	//_sceneWorld->setSpeed(1.0f);

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
    menu->setPositionY(this->getContentSize().height - 100);
    
    //
    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Size layerSize = map->getLayerSize();
    center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    //_viewPort = Layer::create();
    //_viewPort->setPosition(this->getPosition());
    //_viewPort->setContentSize(this->getContentSize());
    //this->addChild(_viewPort);
    
	

    _backgroundLayer = ParallaxNode::create();
    this->addChild(_backgroundLayer, 0, kTagNode);

	/*auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1, 0, 0), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);*/
    
    // add player
    p = Player::createPlayerWithFilename("alienBeige_stand.png");
    p->setTag(kTagPlayer);	
	p->Stand();
	auto body = PhysicsBody::createBox(p->getBoundingBox().size, PhysicsMaterial(0, 0, 0));
	//body->setDynamic(true);
	body->setRotationEnable(false);
	body->setCollisionBitmask(2);
	body->setContactTestBitmask(true);
	
	//body->applyImpulse(cocos2d::Vect(20000, 0));
	p->setPhysicsBody(body);
    this->addChild(p);
    
    _mainLayer = ParallaxNode::create();
    this->addChild(_mainLayer, 2, kTagNode);
    
    map = new TileMap();
    
    // background image
    _backgroundLayer->addChild(map->createLayer(), -1, Vec2(0.7f, 1), origin);
	_mainLayer->addChild(map->createLayer(0), 0, Vec2(1, 1), origin);
    //_backgroundLayer->addChild(map->createLayer(1), 0, Vec2(0.9f, 1), origin);
    //_backgroundLayer->addChild(map->createLayer(2), 0, Vec2(1, 1), origin);
    
    //_mainLayer->addChild(map->createLayer(3), 2, Vec2(1, 1), origin);
    //_mainLayer->addChild(map->createLayer(4), 3, Vec2(1.1f, 1), origin);
    
	log("x:%.1f, y:%.1f", AppGlobal::getInstance()->StartPosition.x, AppGlobal::getInstance()->StartPosition.y);
	p->setPosition(center);
	//log("x:%.1f, y:%.1f", p->getPosition().x * 2.0, p->getPosition().y);
    // add menu "HUD eventually"
    this->addChild(menu);
    
    this->scheduleUpdateWithPriority(42);
    
    //auto startTile = _mainLayer->getChildByTag(2)->getChildByTag(126);
    //Vec2 startPos = Vec2(startTile->getPosition().x, startTile->getPosition().y + 35);
    //p->setPosition(Vec2(200,300));
	//p->Destination = Vec2(200, 300);
    
    //log("anchor X:%.1f, anchor Y:%.1f", p->getAnchorPoint().x, p->getAnchorPoint().y);
    //log("anchor X:%.1f, anchor Y:%.1f", _backgroundLayer->getAnchorPoint().x, _backgroundLayer->getAnchorPoint().y);
    //log("anchor X:%.1f, anchor Y:%.1f", _mainLayer->getAnchorPoint().x, _mainLayer->getAnchorPoint().y);
    
    //log("_backgroundLayer.width: %.1f", _backgroundLayer->getContentSize().width);
    //log("_backgroundLayer.height: %.1f", _backgroundLayer->getContentSize().height);
    
    //log("visibleSize.width: %.1f, visibleSize.height: %.1f", visibleSize.width, visibleSize.height);
    //log("origin.x: %.1f, origin.y: %.1f", origin.x, origin.y);
    //log("layer.width: %.1f, layer.height: %.1f", map->getLayerWidth(), map->getLayerHeight());
    //log("startPositionX: %.1f, startPositionY: %.1f", AppGlobal::getInstance()->StartPosition.x, AppGlobal::getInstance()->StartPosition.y);
    
    //debug = Label::createWithSystemFont("X: 0, Y: 0", "Arial", 24);
    //Label::createWithTTF("label test","fonts/Marker Felt.ttf",32);
    //debug->setPosition(Point(origin.x, origin.y + visibleSize.height - debug->getContentSize().height - 50));
    //debug->setAnchorPoint(Point(0.0f, 0.0f));
    //debug->setColor(Color3B::RED);
    //this->addChild(debug);
    
    
    
    return true;
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
		////(Vec2::ZERO);
		log("contact");
		//a->setDynamic(false);
		
		
		b->setGravityEnable(false);
		//p->getPhysicsBody()->setResting(true);
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

	p->IsSelected = !p->IsSelected;

	//log("mouse X: %.1f, Y: %.1f", touch->getLocation().x, touch->getLocation().y);
	//log("player X: %.1f, Y: %.1f", p->getPosition().x, p->getPosition().y);
	//
	//_mainLayer->stopAllActions();

	

	//float speed = 250.0f;

	//// Get the players position
	//Vec2 start = p->getPosition();
	//// Get the location of the touch
	//Vec2 end = touch->getLocation();

	//

	//// Calculate the distance between the to points
	//float distance = ccpDistance(start, end);

	//float duration = distance / speed;

	//if (rect.containsPoint(touchPoint) == false)
	//{
	//	direction.x = (touchPoint.x > playerPoint.x) ? -1 : 1;
	//	p->Walk(touchPoint);
	//	//_mainLayer->runAction(Sequence::createWithTwoActions(MoveBy::create(duration, Vec2((touchPoint.x > playerPoint.x) ? -distance : distance, 0)), CallFunc::create(CC_CALLBACK_0(GameplayScene::actionFinished, this))));
	//}
	//else if (p->IsJumping == false && rect.containsPoint(touchPoint) && touchPoint.y > playerPoint.y)
	//{
	//	p->Hurt();
	//}
	//else if (p->IsJumping == false && rect.containsPoint(touchPoint) && touchPoint.y < playerPoint.y)
	//{
	//	p->Duck();
	//}


	return true;
}

void GameplayScene::onTouchMoved(Touch* touch, Event  *event)
{
	/*log("mouse X: %.1f, Y: %.1f", touch->getLocation().x, touch->getLocation().y);
	log("player X: %.1f, Y: %.1f", p->getPosition().x, p->getPosition().y);

	Vec2 touchPoint = touch->getLocation();
	Vec2 playerPoint = p->getPosition();
	Rect rect = p->getBoundingBox();*/

	//direction.x = (touchPoint.x > playerPoint.x) ? -1 : 1;
	//p->Flip(touchPoint);
}

void GameplayScene::onTouchEnded(Touch* touch, Event  *event)
{
	direction = Vec2::ZERO;
	p->Stand();

	/*Vec2 touchPoint = touch->getLocation();
	Vec2 playerPoint = p->getPosition();
	Rect rect = p->getBoundingBox();

	if (rect.containsPoint(touchPoint) && touchPoint.y < playerPoint.y || rect.containsPoint(touchPoint) && touchPoint.y > playerPoint.y)
	{
		p->Stand();
	}*/
}

void GameplayScene::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    
    auto diff = touches[0]->getDelta();
    
    //auto node = getChildByTag(kTagNode);
    //auto currentPos = node->getPosition();
    //node->setPosition(currentPos + diff);
    
    Size layerSize = TileMap::getLayerSize();
    Size viewPortSize = _viewPort->getBoundingBox().size;
    
    auto currentPos = _viewPort->getPosition();
    
    float newViewportWorldX = currentPos.x + diff.x;
    float newViewportWorldY = currentPos.y + diff.y;
    
    // Gets the viewport width
    float viewportWidth = layerSize.width - viewPortSize.width;
    float viewportHeight = layerSize.height - viewPortSize.height;
    
    // Checks if viewport can move
    if(newViewportWorldX > -viewportWidth && newViewportWorldX < 0)
        _viewPort->setPositionX(newViewportWorldX);
    if(newViewportWorldY < viewportHeight && newViewportWorldY > 0)
        _viewPort->setPositionY(newViewportWorldY);
    
//    Vector<Node*> children = getChildren();
//    
//    for(int i = 0; i < getChildrenCount(); i++)
//    {
//        auto node = children.at(i);
//        
//        
//    }
//        
//        //node->setPosition(currentPos + diff);
//        //log("%f", child->getPositionX());
    
}

void GameplayScene::update(float delta)
{
	p->Update(delta);

	float x = _mainLayer->getChildByTag(0)->getPositionX();

	x += 400 * delta  * direction.x;

	_mainLayer->getChildByTag(0)->setPositionX(x);


	//for (auto child : _mainLayer->getChildByTag(0)->getChildren())
	//{
	//	float x = child->getPositionX();

	//	x += 400 * delta  * direction.x;

	//	child->setPositionX(x);

	//	//log("%f", Director::getInstance()->getVisibleSize().width);
	//	float width = child->getContentSize().width;

	//	child->setVisible((x > 0 - width) && (x < 1024 + width));

	//	if (child->isVisible())
	//	{
	//		//log("isVisible");
	//	}
	//	//child->getPositionX()
	//}

	//log("%f", _mainLayer->getChildByTag(0)->getPositionX());

    //auto tiles = _mainLayer->getChildByTag(3);
    //
    //for(auto tile : tiles->getChildren())
    //{
    //    if(tile->getBoundingBox().containsPoint(p->getPosition()))
    //    {
    //        log("%i", tile->getTag());
    //    }
    //}
    //
    ////Vec2 startPos = Vec2(startTile->getPosition().x, startTile->getPosition().y + 35);
    //
    //float scale = _viewPort->getScale();
    //
    //std::string vpPos = "_viewPort - X: "+ std::to_string(_viewPort->getPositionX()) +", Y: " + std::to_string(_viewPort->getPositionY());

    //std::string pPos = "_player - X: "+ std::to_string(p->getPositionX() * scale) +", Y: " + std::to_string(p->getPositionY());

    ////std::string testPos = std::to_string(startPos.x);
    //
    //debug->setString(vpPos + "\n" + pPos + "\n");
    //
    //p->Update(delta);
    //
    //Size layerSize = TileMap::getLayerSize() * scale;
    //Size viewPortSize = _viewPort->getBoundingBox().size;
    //
    //// Creates a point that the view port will be drawn to based on the players position
    //// with teh player in the centre
    //float x = p->getPositionX() * scale;
    //float y = p->getPositionY() * scale;
    //
    //float newViewportWorldX = (x - viewPortSize.width / 2) * scale;
    //float newViewportWorldY = (y - viewPortSize.height / 2) * scale;
    //
    //// Gets the viewport width
    //float viewportWidth = layerSize.width - viewPortSize.width;
    //float viewportHeight = layerSize.height - viewPortSize.height;

    //// Checks if viewport can move
    //if(newViewportWorldX < viewportWidth && newViewportWorldX > 0)
    //    _viewPort->setPositionX(-newViewportWorldX);
    //if(newViewportWorldY < viewportHeight && newViewportWorldY > 0)
    //    _viewPort->setPositionY(-newViewportWorldY);

    //log("newViewPortX: %f", newViewportWorldX);
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

void GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    //log("Key with keycode %d pressed", keyCode);
    
    //Node* player = _backgroundLayer->getChildByTag(kTagPlayer);
    
    //player->setPosition(p->getPosition());
    
//    Vector<Node*> children = _backgroundLayer->getChildren();
//    
//    for(int i = 0; i < _backgroundLayer->getChildrenCount(); i++)
//    {
//        Node* child = children.at(i);
//        log("%i", child->getTag());
//    }
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        Scene* menuScene = MenuScene::createScene();
        Director::getInstance()->pushScene(menuScene);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_SHIFT)
    {
        //p->setVelocity(Vec2(600, 600));
        //log("%f", velocity);
    }
    //else if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    //{
    //    p->setDirection(Vec2(-1, 0));
    //    p->Walk(1);
    //}
    //else if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    //{
    //    p->setDirection(Vec2(1, 0));
    //    p->Walk(-1);
    //}
    //else if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    //{
    //    p->setDirection(Vec2(0, 1));
    //    p->Climb();
    //    //p->Jump();
    //}
    //else if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    //{
    //    p->setDirection(Vec2(0, -1));
    //    //p->Crouch();
    //    p->Climb();
    //}
    else if(keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        //direction.y = -1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        //direction.y = 1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        //direction.x = 1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        //direction.x = -1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_Q)
    {
       /* float scale = _viewPort->getScale();
        scale -=  0.1;
        _viewPort->setScale(scale);*/
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_E)
    {
        /*float scale = _viewPort->getScale();
        scale += 0.1;
        _viewPort->setScale(scale);*/
    }
}

void GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    /*direction = Vec2::ZERO;
    
    p->setDirection(Vec2::ZERO);
    p->setVelocity(Vec2(250, 250));
    p->Stand();*/
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
