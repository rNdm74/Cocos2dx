#include "Player.h"
#include "PlayerMenu.h"

USING_NS_CC;

Player::Player()
{
    _PREFIX = "alienBeige";
    
    _spriteFrameCache = SpriteFrameCache::getInstance();

	IsSelected = false;
    
    //addDust();
}

Player* Player::createPlayerWithFilename(std::string spriteFrameName)
{
    auto sprite = new Player();
    
    if(sprite && sprite->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName)))
    {
        sprite->autorelease();
        sprite->setAnchorPoint(Vec2(0.5, 0));
		sprite->setMenu();
		sprite->hideMenu();
		sprite->addEvents();
        sprite->addDust();
      
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

    for(auto child : this->getChildByTag(MENU)->getChildren())
    {
        if(child->getBoundingBox().containsPoint(touchWorldPosition))
        {
            //
            auto scaleUpAction = ScaleTo::create(0.1, 1.0);
            auto scaleDownAction = ScaleTo::create(0.1, 0.8);
            
            // Button effect
            child->runAction(Sequence::createWithTwoActions(scaleUpAction, scaleDownAction));
            
            // Shake
            this->runAction(Repeat::create(ReverseTime::create(MoveBy::create(0.1,Vec2(1, 0))), 10));
            
            // Smoke effect
            addSmoke();
            
            // Delay for smoke to clear
            FiniteTimeAction* waitAction = DelayTime::create(1.0);
            FiniteTimeAction* waitFinished = CallFunc::create(CC_CALLBACK_0(Player::setCharacter, this, child->getTag()));
            
            this->runAction(Sequence::createWithTwoActions(waitAction, waitFinished));
        }
    }

	return true;
}

void Player::setCharacter(int type)
{
    switch (type)
    {
        case 0:
            _PREFIX = "alienBeige";
            //Duck();
            break;
        case 1:
            _PREFIX = "alienBlue";
            //Hurt();
            break;
        case 2:
            _PREFIX = "alienGreen";
            //Jump();
            break;
        case 3:
            _PREFIX = "alienPink";
            //Climb();
            break;
        case 4:
            _PREFIX = "alienYellow";
            break;
    }
    
    this->setSpriteFrame(_PREFIX + _SUFFIX);
}

void Player::setMenu()
{
    const std::vector<std::string> filenames = {"Beige", "Blue", "Green", "Pink", "Yellow"};
    
    int _ptr = 0;
    
    auto menu = Node::create();
    menu->setTag(MENU);
    
    for(auto s : filenames)
    {
        std::string name = "Spritesheets/alien" + s + "_badge2.png";
        auto menu_item = PlayerMenu::createPlayerMenuWithFilename(name);
        menu_item->setTag(_ptr++);
        menu_item->setPosition(getContentSize().width / 2, getContentSize().height / 2);
        menu->addChild(menu_item, -10);
    }
    
    this->addChild(menu);
}

void Player::addSmoke()
{
    auto size = this->getContentSize();//Director::getInstance()->getWinSize();
    _smoke = ParticleSmoke::createWithTotalParticles(900);
    _smoke->setAutoRemoveOnFinish(true);
    _smoke->setTexture(Director::getInstance()->getTextureCache()->addImage("puffSmall.png"));
    
    //The code below we can use both in 2.x and 3.x
    _smoke->setDuration(1);
    _smoke->setGravity(Point(0, 0));  // in Cocos2d-x-2.x CCPoint(0, -240) is used
    _smoke->setAngle(90);
    _smoke->setAngleVar(180);
    _smoke->setRadialAccel(50);
    _smoke->setRadialAccelVar(0);
    _smoke->setTangentialAccel(30);
    _smoke->setTangentialAccelVar(0);
    _smoke->setPosition(Vec2(this->getPositionX(), this->getPositionY() + size.height / 2));
    _smoke->setPosVar(Point(10, 0));
    _smoke->setLife(0.6);
    _smoke->setLifeVar(0.6);
    _smoke->setStartSpin(30);
    _smoke->setStartSpinVar(60);
    _smoke->setEndSpin(60);
    _smoke->setEndSpinVar(60);
    _smoke->setStartColor(Color4F(255,255,255,1));
    _smoke->setStartColorVar(Color4F(0,0,0,0));
    _smoke->setEndColor(Color4F(255, 255, 255, 1));
    _smoke->setEndColorVar(Color4F(0, 0, 0, 0));
    _smoke->setStartSize(15.0f);
    _smoke->setStartSizeVar(0);
    _smoke->setEndSize(50.0f);
    _smoke->setEndSizeVar(0);
    _smoke->setEmissionRate(100);
    
    this->getParent()->addChild(_smoke, 10);
}

void Player::addDust()
{
    _dust = ParticleSmoke::createWithTotalParticles(900);
    _dust->setTexture(Director::getInstance()->getTextureCache()->addImage("3d_green.png"));
    _dust->stopSystem();
    
    this->addChild(_dust, 0);
}

void Player::stopDust()
{
    _dust->stopSystem();
}

void Player::resumeDust()
{
    auto size = this->getContentSize();
    
    float xPos = (_direction.x > 0) ? 12 : size.width - 12;
    
    //The code below we can use both in 2.x and 3.x
    _dust->setDuration(-1);
    _dust->setGravity(Point(800 * -_direction.x, 240));  // in Cocos2d-x-2.x CCPoint(0, -240) is used
    _dust->setAngle(90);
    _dust->setAngleVar(180);
    _dust->setRadialAccel(50);
    _dust->setRadialAccelVar(0);
    _dust->setTangentialAccel(30);
    _dust->setTangentialAccelVar(0);
    _dust->setPosition(xPos, 0);
    _dust->setPosVar(Point(0, 0));
    _dust->setLife(0.2);
    _dust->setLifeVar(0.2);
    _dust->setStartSpin(30);
    _dust->setStartSpinVar(60);
    _dust->setEndSpin(60);
    _dust->setEndSpinVar(60);
    _dust->setStartColor(Color4F(255,255,255,1));
    _dust->setStartColorVar(Color4F(0,0,0,0));
    _dust->setEndColor(Color4F(255, 255, 255, 1));
    _dust->setEndColorVar(Color4F(0, 0, 0, 0));
    _dust->setStartSize(1.0f);
    _dust->setStartSizeVar(0);
    _dust->setEndSize(5.0f);
    _dust->setEndSizeVar(0);
    _dust->setEmissionRate(100);
    _dust->resetSystem();
}

void Player::Update(float delta)
{
    if(IsJumping == false)
    {
        float y = getPositionY();
    
        delta += 6;
    
        y += delta * -1;
    
        setPositionY(y);
    }
}

void Player::showMenu()
{
	IsSelected = true;

	// Sprite looks forward
	this->setSpriteFrame(_PREFIX + _SUFFIX);

	// Stop all running actions
	this->stopAllActions();

	Vec2 center = Vec2(getContentSize().width / 2, 20 + getContentSize().height / 2);

    auto children = this->getChildByTag(MENU)->getChildren();
    
	for (int i = 0; i < children.size(); i++)
	{
		float radians = -0.2 + (i * 50) * (PI / 180);

		float x = center.x + cos(radians) * 80;
		float y = center.y + sin(radians) * 80;

		children.at(i)->runAction(MoveTo::create(0.1f, Vec2(x, y)));
		children.at(i)->runAction(ScaleTo::create(0.1f, 0.8f));
	}

	// Show menu
	
}

void Player::hideMenu()
{
	IsSelected = false;

	// Sprite stands
	this->setSpriteFrame(_PREFIX + _STAND _SUFFIX);

	// Stop all running actions
	this->stopAllActions();

	// Hides menu
	Vec2 center = Vec2(getContentSize().width / 2, getContentSize().height / 2);

    auto children = this->getChildByTag(MENU)->getChildren();
    
    for(auto child : children)
    {
        child->runAction(MoveTo::create(0.1, center));
        child->runAction(ScaleTo::create(0.1f, 0.0f));
    }
}

void Player::Idle()
{
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(ScaleBy::create(4, 1.5));
	actions.pushBack(TintTo::create(4, 255, 0, 0));
	actions.pushBack(FadeTo::create(4, 30));

	auto parallel = Spawn::create(actions);

	this->runAction(parallel);
}

void Player::Walk(Vec2 newLocation)
{	
	this->stopAllActions();
		
	//Set direction to walk
	_direction.x = (newLocation.x > getPositionX()) ? 1 : -1;
	
    //  create the Animation, and populate it with frames fetched from the SpriteFrameCache
    auto _anim = Animation::create();
    
    for (int i = 1; i <= 2; i ++)
    {
        auto fileName = _PREFIX + _WALK + std::to_string(i) + _SUFFIX;
        auto frame = _spriteFrameCache->getSpriteFrameByName(fileName);
        _anim->addSpriteFrame(frame);
    }
    
    //  we can also set timing information
    _anim->setDelayPerUnit(0.1f);
    
    this->runAction(RepeatForever::create(Animate::create(_anim)));

	this->runAction(FlipX::create(_direction.x < 0));
 
    resumeDust();
}

void Player::Stand()
{
	this->stopAllActions();
    
    //
    stopDust();
    
	// Player is not in jumping state
	IsJumping = false;

	//log("Standing");
	this->setSpriteFrame(_PREFIX + _STAND _SUFFIX);
}

void Player::Duck()
{
	this->stopAllActions();
    
    //this->getPhysicsBody()->setEnable(false);
    //this->setAnchorPoint(Vec2::ZERO);
    
    //this->setPositionY();

    this->setSpriteFrame(_PREFIX + _DUCK _SUFFIX);
}

void Player::Jump()
{
	this->stopAllActions();
    
    //this->getPhysicsBody()->setGravityEnable(false);

	// Player is in jumping state
	IsJumping = true;

    this->setSpriteFrame(_PREFIX + _JUMP _SUFFIX);

	FiniteTimeAction* jumpAction = JumpBy::create(0.5f, Vec2(0, 0), 50, 1);
	FiniteTimeAction* jumpFinished = CallFunc::create(CC_CALLBACK_0(Player::Stand, this)); 

	this->runAction(Sequence::createWithTwoActions(jumpAction, jumpFinished));
}

void Player::Climb()
{
	this->stopAllActions();

    //  create the Animation, and populate it with frames fetched from the SpriteFrameCache
    Animation* anim = Animation::create();
    
    for (int i = 1; i <= 2; i ++)
    {
        auto fileName = _PREFIX + _CLIMB + std::to_string(i) + _SUFFIX;
        auto frame = _spriteFrameCache->getSpriteFrameByName(fileName);
        anim->addSpriteFrame(frame);
    }
    
    //  we can also set timing information
    anim->setDelayPerUnit(0.1f);

    this->runAction(RepeatForever::create(Animate::create(anim)));
}

void Player::Hurt()
{
	this->stopAllActions();

    this->setSpriteFrame(_PREFIX + _HURT _SUFFIX);
}

void Player::Flip(Vec2 newLocation)
{
	log("Animation finished");
	this->runAction(FlipX::create(newLocation.x < 0));
}
