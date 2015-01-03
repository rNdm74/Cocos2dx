#ifndef __FranticAlien__GRAPHICS_COMPONENT_H__
#define __FranticAlien__GRAPHICS_COMPONENT_H__

#include "cocos2d.h"

class GameObject;

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject &gameObject) = 0;
};

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
    void update(GameObject &gameObject);
};

#endif /* defined(__FranticAlien__GraphicsComponent__) */
