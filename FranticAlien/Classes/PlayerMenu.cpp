#include "PlayerMenu.h"
#include "Player.h"

USING_NS_CC;

PlayerMenu::PlayerMenu()
{
}

PlayerMenu* PlayerMenu::createPlayerMenuWithFilename(std::string spriteFrameName)
{
	auto sprite = new PlayerMenu();
    
    if(sprite && sprite->initWithFile(spriteFrameName))
    {
        sprite->autorelease();
		
		//sprite->setAnchorPoint(Vec2::ZERO);
        
		sprite->setName(spriteFrameName);
        //sprite->addEvents();

        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void PlayerMenu::addEvents()
{
    auto listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(PlayerMenu::touchEvent, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


bool PlayerMenu::touchEvent(Touch* touch, Event* event)
{
    //touch->
    //
    auto node = event->getCurrentTarget();
    
    auto parent = static_cast<Player*>(node->getParent());
    
    
    if(parent->isSelected())
    {
        MessageBox(node->getName().c_str(), "You have clicked");
    }
    
    return true;
}