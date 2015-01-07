#include "ContactListener.h"
//#include <iostream>


void ContactListener::EndContact(b2Contact* contact)
{
	//b2Fixture* a = contact->GetFixtureA();
	//b2Fixture* b = contact->GetFixtureB();

    log("Contact ended");

    // If one of them is the ground, delete the other
    Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    
	std::vector<Contact>::iterator pos;
    
	pos = std::find(_contacts.begin(), _contacts.end(), myContact);
    
	if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
}

void ContactListener::BeginContact(b2Contact* contact)
{
    // We need to copy out the data because the b2Contact passed in
    // is reused.
	//    b2Fixture* a = contact->GetFixtureA();
	//    b2Fixture* b = contact->GetFixtureB();
	log("Contact begun");
        
    Contact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(myContact);

	//
	//     myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	//    _contacts.push_back(myContact);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    
};

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
    
}