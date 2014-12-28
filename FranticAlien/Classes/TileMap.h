#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "cocos2d.h"

#define TILE_SIZE 69
#define MAX_COLS 17
#define MAX_ROWS 11

class TileMap : public cocos2d::Node
{
private:

public:
	cocos2d::Point startPosition;
	TileMap();
    virtual ~TileMap();

    cocos2d::Node* CreateObjectLayer(int level);
    
    cocos2d::Layer* createLayer();
    cocos2d::Layer* createLayer(int level);
    
    // Getters
    static cocos2d::Size getLayerSize(){ return cocos2d::Size(MAX_COLS * TILE_SIZE, MAX_ROWS * TILE_SIZE); };
    float getLayerWidth() { return MAX_COLS * TILE_SIZE; };
    float getLayerHeight() { return MAX_ROWS * TILE_SIZE; };
};

#endif // __TILEMAP_H__
