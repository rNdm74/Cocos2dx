#ifndef __FranticAlien__GAME_OBJECT_H__
#define __FranticAlien__GAME_OBJECT_H__

#include "cocos2d.h"
#include "Box2D.h"

class MenuComponent;
class InputComponent;
class PhysicsComponent;
class GraphicsComponent;
class b2World;
class b2Shape;
class b2Body;

using namespace cocos2d;

class GameObject : public Sprite
{
	typedef Sprite super;
	typedef GameObject self;

public:
    Vec2 velocity;
    
public:
    // "creator" methods first
	bool isAtTopOfLadder;
	bool isClimbing;
	bool isAtBottomOfLadder;

	Vec2 ladderPos;
    
    // If applicable, then Constructors and the Destructor
	GameObject(MenuComponent* menu, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	{
		_menu = menu;
		_input = input;
		_physics = physics;
		_graphics = graphics;

		isAtTopOfLadder = false;
		isClimbing = false;
		isAtBottomOfLadder = false;

		ladderPos = Vec2::ZERO;
	}

	virtual ~GameObject(){};
    
    // Then the init methods
	virtual void initListeners();

    // Then methods of the instance
	virtual void addMenu();
	virtual void showMenu();
	virtual void hideMenu();
	virtual void update(float& delta, b2World& physics){}

	virtual void addBodyToWorld(b2World& world);
	virtual void addCircularHeadFixtureToBody(float radius, b2Vec2 offset);
	virtual void addCircularBodyFixtureToBody(float radius, b2Vec2 offset);
	virtual void addPolygonShapeToBody();
	virtual	void addRectangularFixtureToBody(float width, float height);
	virtual void addSensorRectangleToBody(float offset);
	virtual void addFixturesToBody(){}
	virtual void createFixture(b2Shape* shape, bool isSensor, uint16 categoryBits, uint16 maskBits);
	virtual void setProperties(ValueMap& properties);

    // Then the overrides
	virtual bool isMenuActive();
	virtual b2Body* getBody() { return _body;  }

protected:
    MenuComponent* _menu;
    InputComponent* _input;
    PhysicsComponent* _physics;
    GraphicsComponent* _graphics;
    
	b2Body* _body;

private:
	bool _selected;

public:
};

class GamePlayer : public GameObject
{
private:
	typedef GameObject super;
	typedef GamePlayer self;

public:
	GamePlayer(MenuComponent* menu, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) 
	: super(menu, input, physics, graphics){}
	
	//
    static GamePlayer* createWithFrameName(const std::string& arg);
 
	//
	void addFixturesToBody();

    //
	virtual void update(float& delta, b2World& physics) override;
};

#endif /* defined(__FranticAlien__GameObject__) */
