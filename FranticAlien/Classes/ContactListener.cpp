#include "Constants.h"
#include "ContactListener.h"
#include "GameObject.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	//log("Contact begun");

	/*Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_contacts.push_back(myContact);*/


	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	

	//check if one of the fixtures is the platform
	b2Fixture* ladderFixture = NULL;
	b2Fixture* gameObjectFixture = NULL;

	if (fixtureA->GetFilterData().categoryBits == kFilterCatagory::LADDER) {
		ladderFixture = fixtureA;
		gameObjectFixture = fixtureB;
	}
	else if (fixtureB->GetFilterData().categoryBits == kFilterCatagory::LADDER) {
		ladderFixture = fixtureB;
		gameObjectFixture = fixtureA;
	}

	if (!ladderFixture)
		return;

	b2Body* ladderBody = ladderFixture->GetBody();
	b2Body* gameObjectBody = gameObjectFixture->GetBody();

	auto ladderTop = ladderBody->GetWorldPoint(b2Vec2(0.5, 1));
	auto gameObjectBottom = gameObjectBody->GetWorldPoint(b2Vec2(0.5, 1));
	log("go.y: %f, lr.y: %f", gameObjectBottom.y, ladderTop.y);

	if (gameObjectBottom.y > ladderTop.y)
	{
		
		//contact->SetEnabled(true);
		//gameObjectBody->SetGravityScale(1);
	}
	else
	{
		log("Touching ladder");
		contact->SetEnabled(false);
		gameObjectBody->SetGravityScale(0);
	}
	

	//int numPoints = contact->GetManifold()->pointCount;
	//b2WorldManifold worldManifold;
	//contact->GetWorldManifold(&worldManifold);

	////check if contact points are moving downward
	//for (int i = 0; i < numPoints; i++) 
	//{
	//	b2Vec2 pointVel = gameObjectBody->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);
	//
	//	if (pointVel.y < 0)
	//		return;//point is moving down, leave contact solid and exit
	//}

	//no points are moving downward, contact should not be solid
	

	GameObject* gameObject;

	if (isLadder(contact, gameObject))
	{
		
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	contact->SetEnabled(true);

    //log("Contact ended");

	// If one of them is the ground, delete the other
	Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };

	std::vector<Contact>::iterator pos;

	pos = std::find(_contacts.begin(), _contacts.end(), myContact);

	if (pos != _contacts.end()) {
		_contacts.erase(pos);
	}

	GameObject* gameObject;

	if (isLadder(contact, gameObject))
	{
		log("Not touching ladder");
		//contact->SetEnabled(true);
		gameObject->getBody()->SetGravityScale(1);
		//b2Vec2 vel = gameObject->getBody()->GetLinearVelocity();

		//gameObject->getBody()->SetLinearVelocity(b2Vec2(vel.x,0));

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