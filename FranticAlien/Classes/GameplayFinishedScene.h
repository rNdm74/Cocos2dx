#ifndef __FranticAlien__GAMEPLAY_FINISHED_SCENE_H__
#define __FranticAlien__GAMEPLAY_FINISHED_SCENE_H__

#include "cocos2d.h"

class GameplayFinishedScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayFinishedScene);
    
private:
    cocos2d::ParallaxNode* _backgroundLayer;
    cocos2d::ParallaxNode* _mainLayer;
    cocos2d::ParallaxNode* _objectLaver;
    cocos2d::ParallaxNode* _hudLayer;
    
    void Pause(Ref* sender);
    void Finished();
};

#endif // __GAMEPLAY_FINISHED_SCENE_H__
