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
