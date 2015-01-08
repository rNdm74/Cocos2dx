#include "AppGlobal.h"
#include "Box2D.h"
#include "Constants.h"
#include "GameObject.h"
#include "InputComponent.h"

void PlayerInputComponent::update(GameObject& gameObject, float& delta)
{
	auto global = AppGlobal::getInstance();

	auto body = gameObject.getBody();

	auto vel = body->GetLinearVelocity();

	float desiredVel = 0.0f;

	float climb = 0.0f;
	
	switch (global->state)
	{
		case STATE_LEFT :  
			desiredVel = b2Max(vel.x - kMinVelocityX, -kMaxVelocityX);
			break;

		case STATE_STOP :  
			desiredVel = vel.x * kStopVelocity;	climb = 0.0f;
			break;

		case STATE_RIGHT : 
			desiredVel = b2Min(vel.x + kMinVelocityX, kMaxVelocityX);
			break;
				
		case STATE_UP:
		{
			climb = 2.5f;

			//if (body->GetGravityScale() == 0)
			//	climb = 5.0f;
		}
		break;

		case STATE_DOWN:
		{
			climb = -5.0f;
			//if (body->GetGravityScale() == 0)
				
		}
		break;
	}

	float velChange = desiredVel - vel.x;
	
	float impulse = body->GetMass() * velChange;
	
	
	body->ApplyLinearImpulse(b2Vec2(impulse, climb), body->GetWorldCenter(), true);
}

void PlayerInputComponent::setLeftVelocityX(float& velocityX)
{
	velocityX = b2Min(velocityX + kMinVelocityX, kMaxVelocityX);
}

void PlayerInputComponent::setRightVelocityX(float& velocityX)
{
	velocityX = b2Max(velocityX - kMinVelocityX, -kMaxVelocityX);
}

void PlayerInputComponent::setStopVelocityX(float& velocityX)
{
	velocityX = velocityX * kStopVelocity;
}

