#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "InputComponent.h"


class Entity
{
public:
    int velocity;
    int x, y;
    
    Entity(){};
    //virtual ~Entity();
    
//    void update(float delta)
//    {
//        _input.update(*this);
//        //physics_.update(*this, world);
//        //graphics_.update(*this, graphics);
//    }
    
private:
    //InputComponent _input;
    
    //InputComponent input_;
    //PhysicsComponent physics_;
    //GraphicsComponent graphics_;
};

#endif // __ENTITY_H__
