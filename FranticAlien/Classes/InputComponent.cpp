#include "AppGlobal.h"
#include "Box2D.h"
#include "Constants.h"
#include "GameObject.h"
#include "InputComponent.h"

void PlayerInputComponent::update(GameObject& gameObject, float& delta)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		gameObject.getBody()->ApplyForceToCenter(b2Vec2(-250,0), true);
	}

	// Move (accelerate) rightwards
	if (GetAsyncKeyState(VK_RIGHT))
	{
		gameObject.getBody()->ApplyForceToCenter(b2Vec2(250, 0), true);
	}

	if (GetAsyncKeyState(VK_UP))
	{
		gameObject.getBody()->ApplyForceToCenter(b2Vec2(0, 500), true);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		gameObject.getBody()->ApplyForceToCenter(b2Vec2(0, -100), true);
	}

}

