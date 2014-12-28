#ifndef __FranticAlien__Player__
#define __FranticAlien__Player__

#include "cocos2d.h"

#define _PREFIX "alienBeige"
#define _SUFFIX ".png"

#define _WALK   "_walk"
#define _DUCK   "_duck"
#define _STAND  "_stand"
#define _JUMP   "_jump"
#define _CLIMB  "_climb"
#define _HURT   "_hurt"

class Player : public cocos2d::Sprite
{
public:
    static Player* createPlayerWithFilename(std::string spriteFrameName);
    
    Player();
    
    void setShadow();
    void Update(float delta);
    void Walk(int direction);
    void Stand();
    void Duck();
    void Jump();
    void Climb();
    void Hurt();
    
    void setVelocity(cocos2d::Vec2 velocity){ _velocity = velocity; };
    void setDirection(cocos2d::Vec2 direction){ _direction = direction; };
    cocos2d::Vec2 getDirection() { return _direction; };
private:
    cocos2d::Vec2 _direction;
    cocos2d::Vec2 _velocity;
    cocos2d::SpriteFrameCache* _spriteFrameCache;
    cocos2d::Sprite* _shadow;
};

#endif /* defined(__FranticAlien__Player__) */
