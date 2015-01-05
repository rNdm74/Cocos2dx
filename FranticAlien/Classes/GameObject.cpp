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
        sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setName("Player");
		sprite->initListeners();
		sprite->addMenu();
		sprite->hideMenu();
                
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void GamePlayer::updateObject(float& delta)
{
	//_physics->update(*this, delta);
	_input->update(*this, delta);
    
}


