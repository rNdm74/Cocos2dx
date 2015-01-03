#ifndef __FranticAlien__INPUT_COMPONENT_H__
#define __FranticAlien__INPUT_COMPONENT_H__

#include "cocos2d.h"

class GameObject;

class InputComponent
{
public:
    virtual ~InputComponent(){};
    virtual void update(GameObject& gameObject) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
    void update(GameObject& gameObject);

private:
    static const int WALK_ACCELERATION = 1;
};

#endif /* defined(__FranticAlien__InputComponent__) */
