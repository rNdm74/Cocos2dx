#include "InputComponent.h"
#include "GameObject.h"
#include "AppGlobal.h"

USING_NS_CC;

void PlayerInputComponent::update(GameObject& gameObject, float& delta)
{
	// Update the player's position
	// IMPORTANT! This must be done after the contact solver
	float playerX = gameObject.getPositionX();
	playerX += gameObject.speedX * delta;
	gameObject.setPositionX(playerX);

	float playerY = gameObject.getPositionY();
	playerY -= gameObject.speedY * delta;
	gameObject.setPositionY(playerY);

	// Process player keyboard input
	bool moveRequest = false;

	if (true)
	{
		// Move (accelerate) leftwards
		if (GetAsyncKeyState(VK_LEFT))
		{
			gameObject.speedX -= gameObject.accX;
			moveRequest = true;
		}

		// Move (accelerate) rightwards
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gameObject.speedX += gameObject.accX;
			moveRequest = true;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			gameObject.speedY -= gameObject.accY;
			moveRequest = true;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			gameObject.speedY += gameObject.accY;
			moveRequest = true;
		}

		// Jump if not already jumping and the jump key was released earlier
		if (GetAsyncKeyState(' ') && !gameObject.jumping && !gameObject.jumpKeyDown)
		{
			gameObject.jumping = true;
			gameObject.jumpKeyDown = true;
			gameObject.speedY = -gameObject.jumpStartSpeedY;
		}

		// Jump key released
		if (!GetAsyncKeyState(' '))
			gameObject.jumpKeyDown = false;

	}

	// Limit the sideways acceleration of the player
	if (gameObject.speedX > gameObject.maxSpeedX) gameObject.speedX = gameObject.maxSpeedX;
	if (gameObject.speedX < -gameObject.maxSpeedX) gameObject.speedX = -gameObject.maxSpeedX;

	// Limit the force of gravity (terminal velocity)
	if (gameObject.speedY > gameObject.maxSpeedY) gameObject.speedY = gameObject.maxSpeedY;
	if (gameObject.speedY < -gameObject.maxSpeedY) gameObject.speedY = -gameObject.maxSpeedY;

	// Apply the force of gravity
	//player.speedY += player.accY;

	// Decelerate the player's sideways movement if left or right wasn't pressed
	if (!moveRequest)
	{
		if (gameObject.speedX < 0) gameObject.speedX += gameObject.decX;
		if (gameObject.speedX > 0) gameObject.speedX -= gameObject.decX;
		if (gameObject.speedY < 0) gameObject.speedY += gameObject.decY;
		if (gameObject.speedY > 0) gameObject.speedY -= gameObject.decY;

		// Deceleration may produce a speed that is greater than zero but
		// smaller than the smallest unit of deceleration. These lines ensure
		// that the player does not keep travelling at slow speed forever after
		// decelerating.
		if (gameObject.speedX > 0 && gameObject.speedX < gameObject.decX) gameObject.speedX = 0;
		if (gameObject.speedX < 0 && gameObject.speedX > -gameObject.decX) gameObject.speedX = 0;
		if (gameObject.speedY > 0 && gameObject.speedY < gameObject.decY) gameObject.speedY = 0;
		if (gameObject.speedY < 0 && gameObject.speedY > -gameObject.decY) gameObject.speedY = 0;
	}
}

