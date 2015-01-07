#ifndef __FranticAlien__GAMEPLAY_FINISHED_SCENE_H__
#define __FranticAlien__GAMEPLAY_FINISHED_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameplayFinishedScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayFinishedScene);
    
private:
    ParallaxNode* _backgroundLayer;
    ParallaxNode* _mainLayer;
    ParallaxNode* _objectLaver;
    ParallaxNode* _hudLayer;
    
    void Pause(Ref* sender);
    void Finished();
};

#endif // __GAMEPLAY_FINISHED_SCENE_H__
