#include "GameObject.h"

USING_NS_CC;

GamePlayer* GamePlayer::createWithFrameName(const std::string& arg)
{
    auto sprite = new GamePlayer
    (
        PlayerMenuComponent::create(),
        new PlayerInputComponent,
        new PlayerPhysicsComponent,
        new PlayerGraphicsComponent
    );
    
    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(arg);
    
    if(sprite && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        sprite->setAnchorPoint(Vec2(0.5, 0));
        //sprite->setMenu();
        //sprite->hideMenu();
        //sprite->addEvents();
        //sprite->addDust();
        
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void GamePlayer::updateObject()
{
    
}
