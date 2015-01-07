#ifndef __FranticAlien__PHYSICS_COMPONENT_H__
#define __FranticAlien__PHYSICS_COMPONENT_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameObject;
class Level;

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent(){};
	virtual void update(GameObject &gameObject) = 0;

protected:

};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	void update(GameObject &gameObject);
	
};

#endif /* defined(__FranticAlien__PhysicsComponent__) */
