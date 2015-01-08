#include "AppGlobal.h"
#include "Box2D.h"
#include "Constants.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "MenuComponent.h"
#include "PhysicsComponent.h"

#pragma region Menu
bool GameObject::isMenuActive() 
{ 
	return _menu->isActive(); 
}

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
#pragma endregion Menu

#pragma region Box2D
void GameObject::addBodyToWorld(b2World& world)
{
	// add a dynamic body to world
	// (subclasses can use other body types by overriding
	// this method and calling body->SetType())
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set
	(
		this->getPositionX() / kPixelsPerMeter,
		this->getPositionY() / kPixelsPerMeter
	);
	
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;
	this->_body = world.CreateBody(&bodyDef);
	
}

void GameObject::addCircularFixtureToBody(float radius)
{
	b2CircleShape shape;
	shape.m_radius = (radius * this->getScale()) / kPixelsPerMeter;
	this->createFixture(&shape, false, kFilterCatagory::PLAYER, kFilterCatagory::BOUNDARY | kFilterCatagory::ENEMY);
}

void GameObject::addRectangularFixtureToBody(float width, float height)
{	
	b2PolygonShape shape;
	shape.SetAsBox
	(
		(width / kPixelsPerMeter) * 0.5f,
		(height / kPixelsPerMeter) * 0.5f,
		b2Vec2(0, 1.1),
		0.0f
	);
	
	this->createFixture(&shape, false, kFilterCatagory::PLAYER, kFilterCatagory::BOUNDARY | kFilterCatagory::ENEMY);
}

void GameObject::addSensorRectangleToBody(float offset)
{
	b2PolygonShape shape;
	shape.SetAsBox
	(
		(10 / kPixelsPerMeter) * 0.5f,
		(10 / kPixelsPerMeter) * 0.5f,
		b2Vec2(0, offset),
		0.0f
	);

	this->createFixture(&shape, true, kFilterCatagory::PLAYER, kFilterCatagory::LADDER);
}

void GameObject::createFixture(b2Shape* shape, bool isSensor, uint16 categoryBits, uint16 maskBits)
{
	// note that friction, etc. can be modified later by looping
	// over the body's fixtures and calling fixture->SetFriction()
	b2FixtureDef fixtureDef;

	fixtureDef.shape = shape;
	fixtureDef.density = kGameObjectFixtureDensity;
	fixtureDef.friction = kGameObjectFixtureFriction;
	//fixtureDef.restitution = kGameObjectFixtureRestitution;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.isSensor = isSensor;

	this->_body->CreateFixture(&fixtureDef);
}

void GameObject::setProperties(ValueMap& properties)
{
	this->setPosition
	(
		Point
		(
			properties["x"].asFloat(),
			properties["y"].asFloat()
		)
	);
}
#pragma endregion Box2D

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

			// GameObject selected effect
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
		sprite->initListeners();
		sprite->addMenu();
		sprite->hideMenu();
		                
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return NULL;
}

void GamePlayer::addFixturesToBody()
{
	auto size = this->getContentSize();
	this->addRectangularFixtureToBody(10,size.height);
	//this->addCircularFixtureToBody(35);
	this->addSensorRectangleToBody(-0.3);
	//this->addSensorRectangleToBody(-0.5);
}

void GamePlayer::update(float& delta, b2World& physics)
{
	_physics->update(*this);
	_input->update(*this, delta);    
	_graphics->update(*this);
}


