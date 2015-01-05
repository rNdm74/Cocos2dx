#ifndef __FranticAlien__SPLASH_SCENE_H__
#define __FranticAlien__SPLASH_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class SplashScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
private:
    void loadMenuScene();
};

#endif // __SPLASH_SCENE_H__
