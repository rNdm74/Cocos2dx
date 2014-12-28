#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

class Entity
{
private:
	SpriteFrameCache* cache;
	SpriteBatchNode* spritebatch;
	Sprite* sprite;

	Point location;

	void WalkFinished();

public:
    Entity(Point p);
    virtual ~Entity();

    SpriteBatchNode* getNode() { return spritebatch; }

    bool isTouched(Point p);

    void setPosition(Point p){ sprite->setPosition(p); }
    Point getPosition() { return sprite->getPosition(); }

    cocos2d::Rect getBoundingBox(){ return sprite->getBoundingBox(); };
    

    void Stand();
    void Walk(Point p);
    void Jump();
    void Crouch();
    void Flip(bool b);

};

#endif // __PLAYER_H__
