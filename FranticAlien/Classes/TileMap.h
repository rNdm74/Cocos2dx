#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "cocos2d.h"
#include "tinyxml2.h"
#include "TileMapObject.h"
#include "AppGlobal.h"

#define TILE_SIZE 69
#define MAX_COLS 17
#define MAX_ROWS 11

class PointObject : public cocos2d::Ref
{
public:
	inline void setRation(cocos2d::Point ratio) { _ratio = ratio; }
	inline void setOffset(cocos2d::Point offset) { _offset = offset; }
	inline void setChild(cocos2d::Node *var) { _child = var; }
	inline cocos2d::Point getOffset() const { return _offset; }
	inline cocos2d::Node* getChild() const { return _child; }
private:
	cocos2d::Point _ratio;
	cocos2d::Point _offset;
	cocos2d::Node* _child;
};

class TileMapObjectGroup : public cocos2d::Ref
{
public:
	std::string _name;	
	std::vector<TileMapObject> _objectInfo;
};

class TileMapLayer : public cocos2d::Ref
{
public:
	std::string _name;
	int _width;
	int _height;

	std::vector<int> _layerInfo;
};

class TileSetTile : public cocos2d::Ref
{
public:
	int _imagewidth;
	int _imageheight;
	std::string _source;
};

class TileSet : public cocos2d::Ref
{
public:
	int _firstgid;
	std::string _name;
	int _tilewidth;
	int _tileheight;

	std::map<int, TileSetTile> _tiles;

	static TileSet* create();
};

class TileMap : public cocos2d::ParallaxNode
{

private:
	std::string _version;
	std::string _orientation;
	std::string _renderorder;
	int _width;
	int _height;
	int _tilewidth;
	int _tileheight;

	TileSet* tileset;
	
	std::vector<TileMapLayer*> layers;
	std::vector<TileMapObjectGroup*> objects;

public:
		
	static TileMap* create(std::string filename);

	bool initWithTMXFile(std::string filename);

	void tilesetswitch(tinyxml2::XMLElement* node);
	void layerswitch(tinyxml2::XMLElement* node);
	void objectgroupswitch(tinyxml2::XMLElement* node);

	void updatePosition();
	
	TileMap();
    virtual ~TileMap();

	static cocos2d::Sprite* createLayer(std::string fileName);
    
    
    // Getters
    static cocos2d::Size getLayerSize(){ return cocos2d::Size(MAX_COLS * TILE_SIZE, MAX_ROWS * TILE_SIZE); };
    float getLayerWidth() { return MAX_COLS * TILE_SIZE; };
    float getLayerHeight() { return MAX_ROWS * TILE_SIZE; };

private:
	void addBackground();
	void addLayers();
};

#endif // __TILEMAP_H__
