#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

//#include "cocos2d.h"
//#include "AppGlobal.h"
#include "Entity.h"

class InputComponent
{
public:
    virtual ~InputComponent() {};
    virtual void update(Entity& player);
};

//class PlayerInputComponent : public InputComponent
//{
//public:
//    virtual void update(Entity& entity)
//    {
//        switch (AppGlobal::getInstance()->getDirection())
//        {
//            case DIR_LEFT:
//                entity.velocity -= WALK_ACCELERATION;
//                break;
//                
//            case DIR_RIGHT:
//                entity.velocity += WALK_ACCELERATION;
//                break;
//                
//            case DIR_UP:
//                break;
//                
//            case DIR_DOWN:
//                break;
//        }
//    }
//    
//private:
//    static const int WALK_ACCELERATION = 1;
//};

#endif // __INPUT_COMPONENT_H__
