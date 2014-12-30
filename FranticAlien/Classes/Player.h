#ifndef __FranticAlien__Player__
#define __FranticAlien__Player__

#include "cocos2d.h"
#include "PlayerMenu.h"

#define _PREFIX "alienBeige"
#define _SUFFIX ".png"

#define _WALK   "_walk"
#define _DUCK   "_duck"
#define _STAND  "_stand"
#define _JUMP   "_jump"
#define _CLIMB  "_climb"
#define _HURT   "_hurt"

#define PI 3.14159265

class Player : public cocos2d::Sprite
{
public:
	bool IsJumping;
	bool IsSelected;

	cocos2d::Vec2 Destination;

public:
    static Player* createPlayerWithFilename(std::string spriteFrameName);
    
    Player();
    
	void addEvents();
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* e);

    void setShadow();
	void setMenu();
	void showMenu();
	void hideMenu();

    void Update(float delta);
	void Idle();
    void Walk(cocos2d::Vec2 newLocation);
    void Stand();
    void Duck();
    void Jump();
    void Climb();
    void Hurt();
	void Flip(cocos2d::Vec2 newLocation);
    
    void setVelocity(cocos2d::Vec2 velocity){ _velocity = velocity; };
    void setDirection(cocos2d::Vec2 direction){ _direction = direction; };
    cocos2d::Vec2 getDirection() { return _direction; };
private:
    cocos2d::Vec2 _direction;
    cocos2d::Vec2 _velocity;
    cocos2d::SpriteFrameCache* _spriteFrameCache;
    cocos2d::Sprite* _shadow;
	cocos2d::Vector<PlayerMenu*> _tick;
	
};

#endif /* defined(__FranticAlien__Player__) */
