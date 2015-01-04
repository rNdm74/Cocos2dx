#include "PhysicsComponent.h"
#include "GameObject.h"

void PlayerPhysicsComponent::update(GameObject &gameObject, float& delta)
{
    //log("%s", gameObject.getSomething());

	this->applyGravity(gameObject, delta);
}

void PlayerPhysicsComponent::applyGravity(GameObject &gameObject, float& delta)
{
	//log("%s", gameObject.getSomething());

	float y = gameObject.getPositionY();

	delta += 6;

	y += delta * -1;

	gameObject.setPositionY(y);
}

void PlayerPhysicsComponent::collisionDetection(GameObject &gameObject, float& delta)
{
	//log("%s", gameObject.getSomething());

	//this->applyGravity(gameObject, delta);
}