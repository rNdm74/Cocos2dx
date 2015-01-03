#ifndef __FranticAlien__MenuComponent__
#define __FranticAlien__MenuComponent__

#define MENU 1
#define PI 3.14159265

#include "cocos2d.h"

class GameObject;

class MenuComponent
{
public:
    virtual ~MenuComponent() {};
    virtual bool showMenu(GameObject &gameObject) = 0;
    virtual bool hideMenu(GameObject &gameObject) = 0;
};

class PlayerMenuComponent : public MenuComponent, public cocos2d::Node
{
public:
    // "creator" methods first
    static PlayerMenuComponent *create();
    
    // init methods
    bool init();
    
    //
    bool showMenu(GameObject &gameObject);
    bool hideMenu(GameObject &gameObject);
    
private:
    const std::string FILE_SUFFIX = "Spritesheets/alien";
    const std::string FILE_PREFIX = "_badge2.png";
    const std::vector<std::string> ITEMS = {"Beige", "Blue", "Green", "Pink", "Yellow"};
};

#endif /* defined(__FranticAlien__MenuComponent__) */
