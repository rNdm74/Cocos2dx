#ifndef __FranticAlien__LEVEL_H__
#define __FranticAlien__LEVEL_H__

#include "cocos2d.h"

using namespace cocos2d;

class Level : public Object
{
public:

	TMXTiledMap *map;

	void loadMap(const char* name);
	TMXTiledMap * getMap();

	Level(void);
	virtual ~Level(void);

	//
};

#endif /* defined(__FranticAlien__LEVEL_H__) */
