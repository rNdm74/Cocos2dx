#ifndef __TILE_MAP_OBJECT_H__
#define __TILE_MAP_OBJECT_H__

#include "cocos2d.h"

class TileMapObject : public cocos2d::Ref
{
public:
	int _gid;
	int _x;
	int _y;
};

#endif // __TILE_MAP_OBJECT_H__
