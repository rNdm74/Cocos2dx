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
	shape.m_radius = radius * this->getScale();
	this->createFixture(&shape, false);
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
	
	this->createFixture(&shape, false);
}
void GameObject::addSensorRectangleToBody()
{
	b2PolygonShape shape;
	shape.SetAsBox
		(
		(50 / kPixelsPerMeter) * 0.5f,
		(10 / kPixelsPerMeter) * 0.5f,
		b2Vec2(0, 0),
		0.0f
		);

	this->createFixture(&shape, true);
}
void GameObject::createFixture(b2Shape* shape, bool isSensor)
{
	// note that friction, etc. can be modified later by looping
	// over the body's fixtures and calling fixture->SetFriction()
	b2FixtureDef fixtureDef;

	fixtureDef.shape = shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	//fixtureDef.restitution = 0.1f;
	fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
	fixtureDef.filter.maskBits = 0xffff;
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

		auto winSize = Director::getInstance()->getWinSize();
		b2Vec2 currentVelocity = this->_body->GetLinearVelocity();
		b2Vec2 impulse(0.0f, 0.0f);

		// walk
		if (touch->getLocation().y < (winSize.height * 0.5f))
		{
			// apply impulse if x velocity is getting low
			if (fabsf(currentVelocity.x) < 5.0f)
			{
				impulse.y = 0.0f;
				impulse.x = 50.0f;
				if (touch->getLocation().x < (winSize.width * 0.5f))
					impulse.x = -impulse.x;
				this->_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
			}
		}
		// jump
		else
		{
			// apply impulse
			impulse.y = 50.0f;
			impulse.x = 30.0f;
			if (touch->getLocation().x < (winSize.width * 0.5f))
				impulse.x = -impulse.x;
			this->_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
		}

		
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
	this->addRectangularFixtureToBody(68,69);
	this->addSensorRectangleToBody();
}

void GamePlayer::update(float& delta, b2World& physics)
{
	_physics->update(*this);
	_input->update(*this, delta);    
}


