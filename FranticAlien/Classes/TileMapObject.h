#ifndef __TILE_MAP_OBJECT_H__
#define __TILE_MAP_OBJECT_H__

#include "cocos2d.h"

class TileMapObject : public cocos2d::Sprite
{
public:
	static TileMapObject* create(int gid, float x, float y);
};

#endif // __TILE_MAP_OBJECT_H__
