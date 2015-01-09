#ifndef __FranticAlien__CONTACT_LISTENER_H__
#define __FranticAlien__CONTACT_LISTENER_H__

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class GameObject;

struct Contact 
{
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;

	bool operator==(const Contact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class ContactListener : public b2ContactListener
{    
private:
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
               
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	virtual bool isLadder(b2Contact* contact, GameObject*& gameObject);
	virtual b2Fixture* getLadderFixture(b2Contact* contact);
	virtual bool isTopLadder(b2Fixture* ladder, GameObject& gameObject);
	virtual bool isBottomLadder(b2Fixture* ladder, GameObject& gameObject);

public:
        std::vector<Contact>_contacts;
};
#endif /* defined(__FranticAlien__CONTACT_LISTENER_H__) */
