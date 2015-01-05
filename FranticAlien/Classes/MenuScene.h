#ifndef __FranticAlien__MENU_SCENE_H__
#define __FranticAlien__MENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MenuScene : public cocos2d::Layer
{
public:
	Sprite* cursor;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

private:
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    
    void Continue(Ref* sender);
    void Play(Ref* sender);
    void Settings(Ref* sender);
    void Quit(Ref* sender);

private:
	Menu* menu;
};

#endif // __MENU_SCENE_H__
