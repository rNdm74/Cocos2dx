#ifndef __FranticAlien__Player__
#define __FranticAlien__Player__

#include "cocos2d.h"
#include "PlayerMenu.h"
#include "Entity.h"

#define _SUFFIX ".png"
#define _WALK   "_walk"
#define _DUCK   "_duck"
#define _STAND  "_stand"
#define _JUMP   "_jump"
#define _CLIMB  "_climb"
#define _HURT   "_hurt"

#define MENU 1

#define PI 3.14159265

class Player : public cocos2d::Sprite
{
private: // VARIABLES
    
    const std::vector<std::string> _PREFIX = { "alienBeige", "alienBlue", "alienGreen", "alienPink", "alienYellow" };
    
    cocos2d::Vec2 _direction;
    cocos2d::Vec2 _velocity;
    cocos2d::SpriteFrameCache* _spriteFrameCache;
    
    cocos2d::ParticleSmoke* _dust;
    cocos2d::ParticleSmoke* _smoke;
    
    bool _isJumping;
    bool _isSelected;

    
public: // GETTER & SETTERS
    void setJumping(bool isJumping) { _isJumping = isJumping;  };
    bool isJumping() { return _isJumping; };

    void setSelected(bool isSelected) { _isSelected = isSelected; };
    bool isSelected() { return _isSelected; };

public: // FUNCTIONS
    Player();
    //virtual ~Player();

    static Player* createPlayerWithFilename(std::string spriteFrameName);
    
	void addEvents();
	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* e);

    void setCharacter(int type);
    
	void setMenu();
	void showMenu();
	void hideMenu();
    
    void addSmoke();
    void addDust();
    void stopDust();
    void resumeDust();

    void update(Entity& entity);
    
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
};

#endif /* defined(__FranticAlien__Player__) */
