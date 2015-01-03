#ifndef __FranticAlien__GAME_OBJECT_H__
#define __FranticAlien__GAME_OBJECT_H__

#include "cocos2d.h"

#include "MenuComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class GameObject : public cocos2d::Sprite
{
public:
    cocos2d::Vec2 velocity;
    
public:
    // "creator" methods first
    
    // If applicable, then Constructors and the Destructor
    GameObject(MenuComponent* menu, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) : _menu(menu), _input(input), _physics(physics), _graphics(graphics){}
    
    virtual ~GameObject(){}
    
    // Then the init methods
    
    // Then methods of the instance
    virtual void updateObject() = 0;
    
    // Then the overrides
    
protected:
    MenuComponent* _menu;
    InputComponent* _input;
    PhysicsComponent* _physics;
    GraphicsComponent* _graphics;
    
private:
    
};

class GamePlayer : public GameObject
{
    using GameObject::GameObject;

public:
    static GamePlayer* createWithFrameName(const std::string& arg);
    
    //
    void updateObject();
};

#endif /* defined(__FranticAlien__GameObject__) */
