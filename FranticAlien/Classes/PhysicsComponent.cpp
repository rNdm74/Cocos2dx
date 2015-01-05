#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Level.h"

void PlayerPhysicsComponent::update(GameObject &gameObject, Level& level, float& delta)
{
    //log("%s", gameObject.getSomething());

	this->applyGravity(gameObject, level, delta);
}

void PlayerPhysicsComponent::applyGravity(GameObject &gameObject, Level& level, float& delta)
{
	//log("%s", gameObject.getSomething());

	float y = gameObject.getPositionY();

	delta += 6;

	y += delta * -1;

	gameObject.setPositionY(y);
}

void PlayerPhysicsComponent::collisionDetection(GameObject &gameObject, Level& level, float& delta)
{
	//log("%s", gameObject.getSomething());

	//this->applyGravity(gameObject, delta);
}