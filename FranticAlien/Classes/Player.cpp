#include "Player.h"

USING_NS_CC;

Player::Player()
{
    _spriteFrameCache = SpriteFrameCache::getInstance();
}

Player* Player::createPlayerWithFilename(std::string spriteFrameName)
{
    auto sprite = new Player();
    
    if(sprite && sprite->initWithSpriteFrameName(spriteFrameName))
    {
        sprite->autorelease();
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setShadow();
        //auto tint = TintTo::create(1, 0, 0, 0);
        //sprite->runAction(tint);
        
//        auto body = PhysicsBody::createEdgeBox(sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
//        body->setDynamic(true);
//        body->setCollisionBitmask(0x000000);
//        sprite->setPhysicsBody(body);
        
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void Player::setShadow()
{
    // Step 1
    _shadow = Sprite::create();
    
    _shadow->setSpriteFrame(this->getSpriteFrame());
    
    // Step 2
    _shadow->setAnchorPoint(Point(0.5,0)); // position it to the center of the target node
    _shadow->setPosition(Point(-1, 0));
    
    // Step 3
    _shadow->setRotation(this->getRotation());
    _shadow->setScale(this->getScale());
    
    // Step 4
    _shadow->setScale(0.9f);
    
    // Step 5
    //shadow->runAction(FlipY::create(true));
    
    // Step 6
    //shadow->setSkewX(calculateSkew(node));
    
    // Step 6
    _shadow->setColor(Color3B(0, 0, 0));
    _shadow->setOpacity(50);
    
    // Step 7
    //shadow->setTag(SHADOW_TAG);
    
    this->addChild(_shadow, -1);
}

void Player::Update(float delta)
{
    auto position = getPosition();
    
    position.x += _velocity.x * delta * _direction.x;
    position.y += _velocity.y * delta * _direction.y;
    
    this->setPosition(position);
    
    //
    _shadow->setSpriteFrame(this->getSpriteFrame());
    
    //log("x: %.1f", getPositionX());
    //log("y: %.1f", getPositionY());
    //log("v: %.1f", _velocity.x);
}

void Player::Walk(int direction)
{
    //  create the Animation, and populate it with frames fetched from the SpriteFrameCache
    auto _anim = Animation::create();
    
    for (int i = 1; i <= 2; i ++)
    {
        auto fileName = _PREFIX _WALK + std::to_string(i) + _SUFFIX;
        auto frame = _spriteFrameCache->getSpriteFrameByName(fileName);
        _anim->addSpriteFrame(frame);
    }
    
    //  we can also set timing information
    _anim->setDelayPerUnit(0.1f);
    
    this->runAction(RepeatForever::create(Animate::create(_anim)));
    
    this->runAction(FlipX::create(_direction.x < 0));
    
    _shadow->runAction(FlipX::create(_direction.x < 0));
}

void Player::Stand()
{
    this->stopAllActions();
    this->setSpriteFrame(_PREFIX _STAND _SUFFIX);
}

void Player::Duck()
{
    this->setSpriteFrame(_PREFIX _DUCK _SUFFIX);
}

void Player::Jump()
{
    this->setSpriteFrame(_PREFIX _JUMP _SUFFIX);
}

void Player::Climb()
{
    //  create the Animation, and populate it with frames fetched from the SpriteFrameCache
    Animation* anim = Animation::create();
    
    for (int i = 1; i <= 2; i ++)
    {
        auto fileName = _PREFIX _CLIMB + std::to_string(i) + _SUFFIX;
        auto frame = _spriteFrameCache->getSpriteFrameByName(fileName);
        anim->addSpriteFrame(frame);
    }
    
    //  we can also set timing information
    anim->setDelayPerUnit(0.1f);
    
    this->runAction(RepeatForever::create(Animate::create(anim)));
}

void Player::Hurt()
{
    this->setSpriteFrame(_PREFIX _HURT _SUFFIX);
}
