#include "GameObject.h"

void GameObject::addMenu()
{
	_menu->addMenu(*this);
}

void GameObject::showMenu()
{
	_menu->showMenu(*this);
}

void GameObject::hideMenu()
{
	_menu->hideMenu(*this);
}

void GameObject::initCollisionPoints()
{
	auto size = this->getBoundingBox().size;

	// Set collision points to test on the player sprite
	collisionPoint.push_back(Vec2(1, 70 - 1));					// Top of head
	collisionPoint.push_back(Vec2(size.width - 1, 70 - 1));		// Top of head
	collisionPoint.push_back(Vec2(1, 0));						// Feet
	collisionPoint.push_back(Vec2(size.width - 1, 0));			// Feet
	collisionPoint.push_back(Vec2(0, 10));						// Left arm
	collisionPoint.push_back(Vec2(0, 70 - 1));					// Left arm
	collisionPoint.push_back(Vec2(size.width, 10));			// Right arm
	collisionPoint.push_back(Vec2(size.width, 70 - 1));		// Right arm
}

void GameObject::initListeners()
{
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {

		auto touchEvent = static_cast<EventTouch*>(event);

		auto node = touchEvent->getCurrentTarget();
		
		if (node->getBoundingBox().containsPoint(touch->getLocation()))
		{
			log("Bingo");
			
			auto player = static_cast<GamePlayer*>(node);

			auto scaleUpAction = ScaleTo::create(0.1, 1.1);
			auto scaleDownAction = ScaleTo::create(0.1, 1.0);

			// Button effect
			node->runAction(Sequence::createWithTwoActions(scaleUpAction, scaleDownAction));

			if (player->isMenuActive())
			{
				player->hideMenu();
			}
			else
			{
				player->showMenu();
			}			
		}

		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

GamePlayer* GamePlayer::createWithFrameName(const std::string& arg)
{
	auto sprite = new GamePlayer
	(
		new PlayerMenuComponent(),
		new PlayerInputComponent(),
		new PlayerPhysicsComponent(),
		new PlayerGraphicsComponent()
	);
    
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(arg);
    
    if(sprite && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        sprite->setAnchorPoint(Vec2(0.5, 0));
		sprite->setName("Player");
		sprite->initCollisionPoints();
		sprite->initListeners();
		sprite->addMenu();
		sprite->hideMenu();
                
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void GamePlayer::updateObject(float& delta, Level& level)
{
	_physics->update(*this, level, delta);
	_input->update(*this, delta);    
}


