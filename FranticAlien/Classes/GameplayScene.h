#ifndef __FranticAlien__GAMEPLAY_SCENE_H__
#define __FranticAlien__GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "TileMap.h"
#include "Player.h"

#define kBackgroundLayer 1
#define kMidgroundLayer 2
#define kForegroundLayer 3
#define PTM_RATIO 32.0

class GameplayScene : public cocos2d::Layer
{
private:
    Player* p;
    cocos2d::Sprite* bg;
    cocos2d::Vec2 center;
    float static velocity ;
    cocos2d::Label* debug;    
        
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
        
	TileMap* tilemap;

    cocos2d::Vec2 direction;

	void actionFinished();
	bool onContactBegin(cocos2d::PhysicsContact &contact);

    void Pause(Ref* sender);
    void GameplaySceneFinished(Ref* sender);
    
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

};

#endif // __GAMEPLAY_SCENE_H__
