#include "Player.h"
#include "PlayerMenu.h"

USING_NS_CC;

Player::Player()
{
    _spriteFrameCache = SpriteFrameCache::getInstance();

	IsSelected = false;

}

Player* Player::createPlayerWithFilename(std::string spriteFrameName)
{
    auto sprite = new Player();
    
    if(sprite && sprite->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName)))
    {
        sprite->autorelease();
		sprite->setScale(2.0f);
        //sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setShadow();
		sprite->setMenu();
		sprite->hideMenu();
		sprite->addEvents();
      
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void Player::addEvents()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Player::touchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Player::touchBegan(Touch* touch, Event* e)
{
	Vec2 touchWorldPosition = convertTouchToNodeSpace(touch);

	for (int i = 0; i < 4; i++)
	{
		//log("touch: %f, %f", touchWorldPosition.x, touchWorldPosition.y);
		Vec2 menuItemWorldPosition = _tick.at(i)->getPosition();
		//log("menu item: %f, %f", menuItemWorldPosition.x, menuItemWorldPosition.y);

		Rect r = _tick.at(i)->getBoundingBox();

		if (r.containsPoint(touchWorldPosition))
		{
			log(_tick.at(i)->getName().c_str());

			switch (i)
			{
			case 0:
				Duck();
				break;
			case 1:
				Hurt();
				break;
			case2:				
				Jump();
				break;
			case 3:
				Climb();
				break;
			default:
				Stand();
				break;
			}
		}
	}

	return true;
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
    //_shadow->setScale(this->getScale());
    
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

void Player::setMenu()
{
	for (int i = 45; i <= 48; i++)
	{
		auto menu_item = PlayerMenu::createPlayerMenuWithFilename("shadedLight" + std::to_string(i) + ".png");
		//menu_item->setSpriteFrame(SpriteFrame::create(, Rect(0, 0, 80, 80)));
		menu_item->setScale(0.5f);
		//menu_item->setAnchorPoint(Point(0.5, 0.5));
		menu_item->setPosition(Point(getContentSize().width / 2, getContentSize().height / 2));
		
		_tick.pushBack(menu_item);

		this->addChild(menu_item, -10);
	}
}

void Player::Update(float delta)
{
	//log("%f", _tick->getPositionX());
	_shadow->setSpriteFrame(this->getSpriteFrame());
}

void Player::showMenu()
{
	// Sprite looks forward
	this->setSpriteFrame(_PREFIX _SUFFIX);

	// Stop all running actions
	this->stopAllActions();

	Vec2 center = Vec2(getContentSize().width / 2, 20 + getContentSize().height / 2);

	for (int i = 0; i < 4; i++)
	{
		float radians = (i * 50) * (PI / 180);

		float x = center.x + cos(radians) * 70;
		float y = center.y + sin(radians) * 70;

		_tick.at(i)->runAction(MoveTo::create(0.1, Vec2(x, y)));
	}

	// Show menu
	
}

void Player::hideMenu()
{
	// Sprite stands
	this->setSpriteFrame(_PREFIX _STAND _SUFFIX);

	// Stop all running actions
	this->stopAllActions();

	// Hides menu
	Vec2 center = Vec2(getContentSize().width / 2, getContentSize().height / 2);

	for (int i = 0; i < 4; i++)
	{	
		_tick.at(i)->runAction(MoveTo::create(0.1, center));
	}
}

void Player::Idle()
{
	
}

void Player::Walk(Vec2 newLocation)
{	
	this->stopAllActions();

	/*float speed = 250.0f;

	Vec2 start = getPosition();
	Vec2 end = newLocation;

	float distance = ccpDistance(start, end);

	float duration = distance / speed;

	this->runAction(Sequence::createWithTwoActions(MoveBy::create(duration, Vec2(end.x, start.y)), CallFunc::create(CC_CALLBACK_0(Player::Stand, this))));*/

	//Set direction to walk
	_direction.x = (newLocation.x > getPositionX()) ? 1 : -1;
	
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

	_direction = Vec2::ZERO;

	float resetPositionX = getContentSize().width / 2;
	float resetPositionY = getContentSize().height / 2;

	//log("%f", resetPosition);

	//if ()
	//_tick->runAction(MoveTo::create(0.1, Point(resetPositionX, resetPositionY)));

	// Player is not in jumping state
	IsJumping = false;

	//log("Standing");
	//this->setSpriteFrame(_PREFIX _STAND _SUFFIX);

	//Idle();
}

void Player::Duck()
{
    this->setSpriteFrame(_PREFIX _DUCK _SUFFIX);

	//FiniteTimeAction* waitAction = DelayTime::create(0.1);
	//FiniteTimeAction* waitFinished = CallFunc::create(CC_CALLBACK_0(Player::Stand, this));

	//this->runAction(Sequence::createWithTwoActions(waitAction, waitFinished));
}

void Player::Jump()
{
	//this->stopAllActions();

	// Player is in jumping state
	IsJumping = true;

    this->setSpriteFrame(_PREFIX _JUMP _SUFFIX);

	FiniteTimeAction* jumpAction = JumpBy::create(0.5f, Vec2(0, 0), 50, 1);
	FiniteTimeAction* jumpFinished = CallFunc::create(CC_CALLBACK_0(Player::Stand, this)); 

	this->runAction(Sequence::createWithTwoActions(jumpAction, jumpFinished));
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

void Player::Flip(Vec2 newLocation)
{
	log("Animation finished");
	this->runAction(FlipX::create(newLocation.x < 0));
}
