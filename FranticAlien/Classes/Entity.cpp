#include "Entity.h"

USING_NS_CC;

Entity::Entity(cocos2d::Point p)
{
	location = p;

	cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile("alienBeige.plist");

	spritebatch = SpriteBatchNode::create("alienBeige.pvr.ccz");

	sprite = cocos2d::Sprite::createWithSpriteFrameName("alienBeige_stand.png");
    sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(p);
    
    // Add the sprite to the spritebatch
	spritebatch->addChild(sprite);
}

Entity::~Entity()
{
}

void Entity::Stand()
{
    sprite->stopAllActions();
    
    sprite->setSpriteFrame(cache->getSpriteFrameByName("alienBeige_stand.png"));
}

void Entity::Walk(Point p)
{
    Vector<cocos2d::SpriteFrame*> frames(2);

	for(int i = 1; i <= 2; i++)
	{
        String* fileName = String::createWithFormat("alienBeige_walk%d.png", i);

		SpriteFrame* frame = cache->getSpriteFrameByName(fileName->getCString());
	   	frames.pushBack(frame);
	}

	Animation* runAnim = Animation::createWithSpriteFrames(frames, 0.1f);
	sprite->setSpriteFrame(cache->getSpriteFrameByName("alienBeige_walk1.png"));

	// Create action that will be repeated forever
	Action* action = RepeatForever::create(Animate::create(runAnim));

	// Execute walking action
	sprite->runAction(action);

	// Check sprite direction
	sprite->runAction(FlipX::create(p.x > 0));
    
//    auto position = sprite->getPosition();
//    
//    position.x += 1 * p.x;
//
//    sprite->setPosition(position);
}

void Entity::WalkFinished()
{

	Stand();
}

void Entity::Jump()
{
	sprite->setSpriteFrame(cache->getSpriteFrameByName("alienBeige_jump.png"));
	
    FiniteTimeAction* actionJump = JumpBy::create(0.3, Point(0, 0), 50, 1);

    FiniteTimeAction* actionJumpDone = CallFuncN::create(CC_CALLBACK_0(Entity::WalkFinished, this));

    spritebatch->runAction(Sequence::createWithTwoActions(actionJump, actionJumpDone));
}

void Entity::Crouch()
{
    sprite->setSpriteFrame(cache->getSpriteFrameByName("alienBeige_duck.png"));
}

void Entity::Flip(bool b)
{
}

bool Entity::isTouched(Point p)
{
	float x = sprite->getPosition().x;
	float y = sprite->getPosition().y - sprite->getContentSize().height;
	float width = sprite->getContentSize().width;
	float height = sprite->getContentSize().height;

	Rect r = Rect(x, y, width, height);

	return(r.containsPoint(p));
}
