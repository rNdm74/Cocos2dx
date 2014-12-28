#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "Box2D.h"

#define kBackgroundLayer 1
#define kMidgroundLayer 2
#define kForegroundLayer 3
#define PTM_RATIO 32.0

class GameplayScene : public cocos2d::Layer
{
private:
    TileMap* map;
    Entity* player;
    Player* p;
    Sprite* bg;
    Vec2 center;
    float velocity = 250;
    cocos2d::Label* debug;
    b2World* _world;
    b2Body* _body;
    
        
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);
    
    void update(float) override;
    
private:
    cocos2d::PhysicsWorld* _sceneWorld;
    void setPhysicsWorld(cocos2d::PhysicsWorld* sceneWorld) { _sceneWorld = sceneWorld; };
    
    cocos2d::ParallaxNode* _backgroundLayer;
    cocos2d::ParallaxNode* _mainLayer;
    //cocos2d::ParallaxNode* _objectLaver;
    cocos2d::Layer* _viewPort;
    
    cocos2d::Vec2 direction = cocos2d::Vec2::ZERO;
    
    void Pause(Ref* sender);
    void GameplaySceneFinished(Ref* sender);
    
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};

#endif // __GAMEPLAY_SCENE_H__
