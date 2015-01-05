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
	virtual void update(GameObject &gameObject, Level& level, float& delta) = 0;
	virtual void applyGravity(GameObject &gameObject, Level& level, float& delta) = 0;
	virtual void collisionDetection(GameObject &gameObject, Level& level, float& delta) = 0;
};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	void update(GameObject &gameObject, Level& level, float& delta);
	void applyGravity(GameObject &gameObject, Level& level, float& delta);
	void collisionDetection(GameObject &gameObject, Level& level, float& delta);
};

#endif /* defined(__FranticAlien__PhysicsComponent__) */
