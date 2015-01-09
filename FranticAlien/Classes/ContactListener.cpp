#include "Constants.h"
#include "ContactListener.h"
#include "GameObject.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	GameObject* gameObject;

	if (isLadder(contact, gameObject))
	{
		log("Touching ladder");
		contact->SetEnabled(false);

		auto ladder = getLadderFixture(contact);
		ladder->SetSensor(true);

		if (isTopLadder(ladder, *gameObject))
		{
			log("Entered top of ladder");
		}
		else if (isBottomLadder(ladder, *gameObject))
		{
			log("Entered bottom of ladder");
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{	
	GameObject* gameObject;

	if (isLadder(contact, gameObject))
	{
		log("Not touching ladder");
		contact->SetEnabled(true);

		auto ladder = getLadderFixture(contact);

		if (isTopLadder(ladder, *gameObject))
		{
			log("Exited top of ladder");
		}		
		else if (isBottomLadder(ladder, *gameObject))
		{
			log("Exited bottom of ladder");
		}

	}		
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    
}

bool ContactListener::isLadder(b2Contact* contact, GameObject*& gameObject)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure only one of the fixtures was a sensor
	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();
	
	if (!(sensorA ^ sensorB))
		return false;
		
	if (sensorA) // fixtureA must be player
	{
		gameObject = static_cast<GameObject*>(fixtureA->GetBody()->GetUserData());
	}
	else // fixtureB must be player
	{		
		gameObject = static_cast<GameObject*>(fixtureB->GetBody()->GetUserData());
	}

	return true;
}

b2Fixture* ContactListener::getLadderFixture(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetFilterData().categoryBits == kFilterCatagory::LADDER) 
		return fixtureA;
	else if (fixtureB->GetFilterData().categoryBits == kFilterCatagory::LADDER) 
		return fixtureB;
}

bool ContactListener::isTopLadder(b2Fixture* ladder, GameObject& gameObject)
{
	auto top = ladder->GetBody()->GetWorldPoint(b2Vec2(0.5, 1)); // middle, top

	auto pos = gameObject.getBody()->GetWorldPoint(b2Vec2(0.5, 0)); // middle, bottom

	return pos.y > top.y;
}

bool ContactListener::isBottomLadder(b2Fixture* ladder, GameObject& gameObject)
{
	auto bottom = ladder->GetBody()->GetWorldPoint(b2Vec2(0.5, 0)); // middle, top

	auto pos = gameObject.getBody()->GetWorldPoint(b2Vec2(0.5, 0)); // middle, bottom

	return true;
}