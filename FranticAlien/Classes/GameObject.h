#ifndef __FranticAlien__GAME_OBJECT_H__
#define __FranticAlien__GAME_OBJECT_H__

#include "cocos2d.h"

#include "MenuComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

using namespace cocos2d;

class GameObject : public Sprite
{
public:
    Vec2 velocity;
    
public:
    // "creator" methods first
    
    // If applicable, then Constructors and the Destructor
	GameObject(MenuComponent* menu, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	{
		_menu = menu;
		_input = input;
		_physics = physics;
		_graphics = graphics;

		// Set acceleration and speed
		float mScale = 60.f;

		accX = 0.2f * mScale;
		decX = 0.3f * mScale;
		maxSpeedX = 5.0f * mScale;
		maxSpeedY = 10.0f * mScale;

		speedX = 0.f;
		speedY = 0.f;

		// Set jump and gravity forces
		jumpStartSpeedY = 8.f * mScale;
		accY = 0.2f * mScale;
		decY = 0.3f * mScale;

		jumping = false;
		jumpKeyDown = false;

		// Set collision points to test on the player sprite
		collisionPoint.push_back(Vec2(10, 92)); // Top of head
		collisionPoint.push_back(Vec2(56, 92)); // Top of head
		collisionPoint.push_back(Vec2(10, 0));	// Feet
		collisionPoint.push_back(Vec2(56, 40)); // Feet
		collisionPoint.push_back(Vec2(0, 50));  // Left arm
		collisionPoint.push_back(Vec2(0, 40));  // Left arm
		collisionPoint.push_back(Vec2(66, 50)); // Right arm
		collisionPoint.push_back(Vec2(66, 40)); // Right arm
	}

	virtual ~GameObject(){};
    
    // Then the init methods
	virtual void initListeners();

    // Then methods of the instance
	virtual void addMenu();
	virtual void showMenu();
	virtual void hideMenu();
	virtual void updateObject(float& delta){}
		    
    // Then the overrides
	virtual bool isMenuActive() { return _menu->isActive(); }

protected:
    MenuComponent* _menu;
    InputComponent* _input;
    PhysicsComponent* _physics;
    GraphicsComponent* _graphics;
    
private:
	bool _selected;

public:
	// The player's current position (top-left co-ordinate of sprite)
	float playerX, playerY;

	// The width and height of the player sprite
	int playerW, playerH;

	// The amount of X acceleration to apply when the player moves left or right
	// The amount of X deceleration to apply when the player does not move left or right
	float accX, decX;

	// The amount of X and Y movement to occur on the next frame
	float speedX, speedY;

	// The maximum movement speed allowed for the player
	float maxSpeedX, maxSpeedY;

	// The amount of upward force to apply when the player first presses jump
	float jumpStartSpeedY;

	// The amount of Y acceleration to apply on each frame due to the force of gravity
	float accY, decY;

	// Collision points to test on the player sprite
	std::vector<Vec2> collisionPoint;

	// Geometric version of player
	//Geometry playerGeom;

	// True if currently jumping (prevents the player jumping while in mid-air)
	bool jumping;

	// True if the jump key is currently held down (key must be released to allow a new jump)
	bool jumpKeyDown;

};

class GamePlayer : public GameObject
{
public:
	GamePlayer(MenuComponent* menu, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) 
				 : GameObject(menu, input, physics, graphics){}
	//
    static GamePlayer* createWithFrameName(const std::string& arg);
 
    //
    virtual void updateObject(float& delta) override;
};

#endif /* defined(__FranticAlien__GameObject__) */
