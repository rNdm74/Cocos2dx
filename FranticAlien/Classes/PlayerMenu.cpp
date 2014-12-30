#include "PlayerMenu.h"

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

        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}