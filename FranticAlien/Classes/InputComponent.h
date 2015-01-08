#ifndef __FranticAlien__INPUT_COMPONENT_H__
#define __FranticAlien__INPUT_COMPONENT_H__

#include "cocos2d.h"

class GameObject;

using namespace cocos2d;

class InputComponent
{
public:
    virtual ~InputComponent(){};
    virtual void update(GameObject& gameObject, float& delta) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
	void update(GameObject& gameObject, float& delta);

private:	
	void setLeftVelocityX(float& velocityX);
	void setRightVelocityX(float& velocityX);
	void setStopVelocityX(float& velocityX);
};

#endif /* defined(__FranticAlien__InputComponent__) */
