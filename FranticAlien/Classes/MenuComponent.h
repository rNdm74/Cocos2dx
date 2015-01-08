#ifndef __FranticAlien__MenuComponent__
#define __FranticAlien__MenuComponent__

#include "cocos2d.h"

using namespace cocos2d;

class GameObject;

class MenuComponentItem : public Sprite
{
public:
	static MenuComponentItem* createMenuWithFrameName(std::string frameName);

	void initListeners();
};

class MenuComponent
{
public:
	//
    virtual ~MenuComponent() {};

	//
	virtual bool addMenu(GameObject &gameObject) = 0;
    virtual void showMenu(GameObject &gameObject) = 0;
	virtual void hideMenu(GameObject &gameObject) = 0;

	virtual void update(GameObject &gameObject) = 0;
	
	virtual bool isActive() = 0;
};

class PlayerMenuComponent : public MenuComponent
{
public:    
    // init methods
	bool addMenu(GameObject &gameObject);
	void showMenu(GameObject &gameObject);
	void hideMenu(GameObject &gameObject);
    
	void update(GameObject &gameObject){}

	inline bool isActive() { return _isActive; }

private:
	bool _isActive;
};

#endif /* defined(__FranticAlien__MenuComponent__) */
