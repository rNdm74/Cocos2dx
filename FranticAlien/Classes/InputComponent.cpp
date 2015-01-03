#include "InputComponent.h"
#include "GameObject.h"
#include "AppGlobal.h"

USING_NS_CC;

void PlayerInputComponent::update(GameObject& gameObject)
{
    switch (AppGlobal::getInstance()->getDirection())
    {
        case DIR_LEFT:
            gameObject.velocity.x -= WALK_ACCELERATION;
            break;
            
        case DIR_RIGHT:
            gameObject.velocity.x += WALK_ACCELERATION;
            break;
        
        case DIR_UP:
            gameObject.velocity.y += WALK_ACCELERATION;
            break;
        
        case DIR_DOWN:
            gameObject.velocity.y -= WALK_ACCELERATION;
            break;
    }
}

