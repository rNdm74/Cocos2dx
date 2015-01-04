#ifndef __FranticAlien__PHYSICS_COMPONENT_H__
#define __FranticAlien__PHYSICS_COMPONENT_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameObject;

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent(){};
	virtual void update(GameObject& gameObject, float& delta) = 0;
	virtual void applyGravity(GameObject& gameObject, float& delta) = 0;
	virtual void collisionDetection(GameObject& gameObject, float& delta) = 0;
};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    void update(GameObject& gameObject, float& delta);
	void applyGravity(GameObject& gameObject, float& delta);
	void collisionDetection(GameObject& gameObject, float& delta);
};

#endif /* defined(__FranticAlien__PhysicsComponent__) */
