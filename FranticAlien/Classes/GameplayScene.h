#ifndef __FranticAlien__GAMEPLAY_SCENE_H__
#define __FranticAlien__GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "TileMap.h"
#include "Player.h"
#include "World.h"

#define kBackgroundLayer 1
#define kMidgroundLayer 2
#define kForegroundLayer 3
#define PTM_RATIO 32.0

using namespace cocos2d;

class GameplayScene : public Layer
{
private:
	World* world;
    GamePlayer* player;
    Vec2 center;   
        
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayScene);
    
    void update(float) override;
    
private:
        
	TileMap* tilemap;

    cocos2d::Vec2 direction;

	void actionFinished();
	bool onContactBegin(PhysicsContact &contact);

    void Pause(Ref* sender);
    void GameplaySceneFinished(Ref* sender);
    
	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchMoved(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);

    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

};

#endif // __GAMEPLAY_SCENE_H__
