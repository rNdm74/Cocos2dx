#ifndef __FranticAlien__PlayerMenu__
#define __FranticAlien__PlayerMenu__

#include "cocos2d.h"

class PlayerMenu : public cocos2d::Sprite
{
public:
	static PlayerMenu* createPlayerMenuWithFilename(std::string spriteFrameName);    
	PlayerMenu();
    
    void addEvents();
    bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__FranticAlien__PlayerMenu__) */
