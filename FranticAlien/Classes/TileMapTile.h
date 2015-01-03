#ifndef __FranticAlien__TILE_MAP_TILE_H__
#define __FranticAlien__TILE_MAP_TILE_H__

#include "cocos2d.h"

#define PI 3.14159265

class TileMapTile : public cocos2d::Sprite
{
public:
	static TileMapTile* create(float x, float y, int gid);
    TileMapTile();
    
    void setShadow(cocos2d::Vec2 offset);
    void updateShadow();
    void setLightPosition(cocos2d::Vec2 lightPosition){ _lightPosition = lightPosition; };
    
private:
    cocos2d::Vec2 _lightPosition;
    cocos2d::Sprite* _shadow;
    float calculateSkew();
    float toDegrees(float radians){ return tan(radians * PI / 180); };
};

#endif // __TILE_MAP_TILE_H__
