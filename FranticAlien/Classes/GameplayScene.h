#ifndef __FranticAlien__GAMEPLAY_SCENE_H__
#define __FranticAlien__GAMEPLAY_SCENE_H__

#include "cocos2d.h"

class World;

using namespace cocos2d;

class GameplayScene : public Layer
{
private:
	World* world;
        
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
