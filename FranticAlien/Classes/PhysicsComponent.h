#ifndef __FranticAlien__PHYSICS_COMPONENT_H__
#define __FranticAlien__PHYSICS_COMPONENT_H__

#include "cocos2d.h"

class GameObject;

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent(){};
    virtual void update(GameObject& gameObject) = 0;
};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    void update(GameObject& gameObject);
};

#endif /* defined(__FranticAlien__PhysicsComponent__) */
