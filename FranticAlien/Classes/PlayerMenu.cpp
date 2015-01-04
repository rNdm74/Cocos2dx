#include "PlayerMenu.h"
#include "Player.h"

USING_NS_CC;


PlayerMenu* PlayerMenu::createPlayerMenuWithFilename(std::string spriteFrameName)
{
	auto sprite = new PlayerMenu();
    
    if(sprite && sprite->initWithFile(spriteFrameName))
    {
        sprite->autorelease();
		//sprite->setAnchorPoint(Vec2::ZERO);
        
		sprite->setName(spriteFrameName);
        
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void PlayerMenu::initListeners()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {

		auto touchEvent = static_cast<EventTouch*>(event);

		auto node = touchEvent->getCurrentTarget();
		//auto pos = node->convertTouchToNodeSpace();
		
		if (node->getBoundingBox().containsPoint(touch->getLocation()))
		{
			//log("Bingo");
			log(node->getName().c_str());

			/*auto player = static_cast<GamePlayer*>(node);

			if (player->isMenuActive())
			{
				player->hideMenu();
			}
			else
			{
				player->showMenu();
			}*/
		}

		return true;
	};

    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
