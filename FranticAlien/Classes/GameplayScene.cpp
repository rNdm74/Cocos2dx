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
    //enable debug draw
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(GameplayScene::onTouchesMoved, this);
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
    menu->setPositionY(this->getContentSize().height - 100);
    
    //
    //
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Size layerSize = map->getLayerSize();
    center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    _viewPort = Layer::create();
    _viewPort->setPosition(this->getPosition());
    _viewPort->setContentSize(this->getContentSize());
    this->addChild(_viewPort);
    
    _backgroundLayer = ParallaxNode::create();
    _viewPort->addChild(_backgroundLayer, 0, kTagNode);
    
    // add player
    p = Player::createPlayerWithFilename("alienBeige_stand.png");
    p->setTag(kTagPlayer);
    
    _viewPort->addChild(p, 1);
    _viewPort->setPositionY(-70);
    
    _mainLayer = ParallaxNode::create();
    _viewPort->addChild(_mainLayer, 2, kTagNode);
    
    map = new TileMap();
    
    // background image
    _backgroundLayer->addChild(map->createLayer(), -1, Vec2(0.7f, 1), origin);
    _backgroundLayer->addChild(map->createLayer(0), 0, Vec2(0.7f, 1), origin);
    _backgroundLayer->addChild(map->createLayer(1), 0, Vec2(0.9f, 1), origin);
    _backgroundLayer->addChild(map->createLayer(2), 0, Vec2(1, 1), origin);
    
    _mainLayer->addChild(map->createLayer(3), 2, Vec2(1, 1), origin);
    _mainLayer->addChild(map->createLayer(4), 3, Vec2(1.1f, 1), origin);
    
    // add menu "HUD eventually"
    this->addChild(menu);
    
    this->scheduleUpdateWithPriority(42);
    
    //auto startTile = _mainLayer->getChildByTag(2)->getChildByTag(126);
    //Vec2 startPos = Vec2(startTile->getPosition().x, startTile->getPosition().y + 35);
    //p->setPosition(startPos);
    
    
    //log("anchor X:%.1f, anchor Y:%.1f", p->getAnchorPoint().x, p->getAnchorPoint().y);
    //log("anchor X:%.1f, anchor Y:%.1f", _backgroundLayer->getAnchorPoint().x, _backgroundLayer->getAnchorPoint().y);
    //log("anchor X:%.1f, anchor Y:%.1f", _mainLayer->getAnchorPoint().x, _mainLayer->getAnchorPoint().y);
    
    log("_backgroundLayer.width: %.1f", _backgroundLayer->getContentSize().width);
    //log("_backgroundLayer.height: %.1f", _backgroundLayer->getContentSize().height);
    
    log("visibleSize.width: %.1f, visibleSize.height: %.1f", visibleSize.width, visibleSize.height);
    log("origin.x: %.1f, origin.y: %.1f", origin.x, origin.y);
    log("layer.width: %.1f, layer.height: %.1f", map->getLayerWidth(), map->getLayerHeight());
    log("startPositionX: %.1f, startPositionY: %.1f", AppGlobal::getInstance()->StartPosition.x, AppGlobal::getInstance()->StartPosition.y);
    
    debug = Label::createWithSystemFont("X: 0, Y: 0", "Arial", 24);
    //Label::createWithTTF("label test","fonts/Marker Felt.ttf",32);
    debug->setPosition(Point(origin.x, origin.y + visibleSize.height - debug->getContentSize().height - 50));
    debug->setAnchorPoint(Point(0.0f, 0.0f));
    debug->setColor(Color3B::RED);
    this->addChild(debug);
    
    
    
    return true;
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
    auto tiles = _mainLayer->getChildByTag(3);
    
    for(auto tile : tiles->getChildren())
    {
        if(tile->getBoundingBox().containsPoint(p->getPosition()))
        {
            log("%i", tile->getTag());
        }
    }
    
    //Vec2 startPos = Vec2(startTile->getPosition().x, startTile->getPosition().y + 35);
    
    float scale = _viewPort->getScale();
    
    std::string vpPos = "_viewPort - X: "+ std::to_string(_viewPort->getPositionX()) +", Y: " + std::to_string(_viewPort->getPositionY());

    std::string pPos = "_player - X: "+ std::to_string(p->getPositionX() * scale) +", Y: " + std::to_string(p->getPositionY());

    //std::string testPos = std::to_string(startPos.x);
    
    debug->setString(vpPos + "\n" + pPos + "\n");
    
    p->Update(delta);
    
    Size layerSize = TileMap::getLayerSize() * scale;
    Size viewPortSize = _viewPort->getBoundingBox().size;
    
    // Creates a point that the view port will be drawn to based on the players position
    // with teh player in the centre
    float x = p->getPositionX() * scale;
    float y = p->getPositionY() * scale;
    
    float newViewportWorldX = (x - viewPortSize.width / 2) * scale;
    float newViewportWorldY = (y - viewPortSize.height / 2) * scale;
    
    // Gets the viewport width
    float viewportWidth = layerSize.width - viewPortSize.width;
    float viewportHeight = layerSize.height - viewPortSize.height;

    // Checks if viewport can move
    if(newViewportWorldX < viewportWidth && newViewportWorldX > 0)
        _viewPort->setPositionX(-newViewportWorldX);
    if(newViewportWorldY < viewportHeight && newViewportWorldY > 0)
        _viewPort->setPositionY(-newViewportWorldY);

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
        p->setVelocity(Vec2(600, 600));
        //log("%f", velocity);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        p->setDirection(Vec2(-1, 0));
        p->Walk(1);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        p->setDirection(Vec2(1, 0));
        p->Walk(-1);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        p->setDirection(Vec2(0, 1));
        p->Climb();
        //p->Jump();
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        p->setDirection(Vec2(0, -1));
        //p->Crouch();
        p->Climb();
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        direction.y = -1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        direction.y = 1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        direction.x = 1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        direction.x = -1;
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_Q)
    {
        float scale = _viewPort->getScale();
        scale -=  0.1;
        _viewPort->setScale(scale);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_E)
    {
        float scale = _viewPort->getScale();
        scale += 0.1;
        _viewPort->setScale(scale);
    }
}

void GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    direction = Vec2::ZERO;
    
    p->setDirection(Vec2::ZERO);
    p->setVelocity(Vec2(250, 250));
    p->Stand();
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
