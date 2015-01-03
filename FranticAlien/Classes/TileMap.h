#ifndef __FranticAlien__TILEMAP_H__
#define __FranticAlien__TILEMAP_H__

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
    inline void setName(std::string name) { _name = name; }
    inline void setObjectInfo(std::vector<TileMapObject> objectInfo) { _objectInfo = objectInfo; }
    inline std::string getName(){ return _name; }
    inline std::vector<TileMapObject> getObjectInfo() { return _objectInfo; }
private:
	std::string _name;	
	std::vector<TileMapObject> _objectInfo;
};

class TileMapLayer : public cocos2d::Ref
{
public:
    inline void setName(std::string name) { _name = name; }
    inline void setWidth(int width) { _width = width; }
    inline void setHeight(int height) { _height = height; }
    inline void setLayerInfo(std::vector<int> layerInfo) { _layerInfo = layerInfo; }
    inline std::string getName() { return _name; }
    inline int getWidth() { return _width; }
    inline int getHeight() { return _height; }
    inline std::vector<int> getLayerInfo() { return _layerInfo; }
    inline int getLayerInfoAt(int index) { return _layerInfo[index]; }
private:
	std::string _name;
	int _width;
	int _height;
	std::vector<int> _layerInfo;
};

class TileSetTile : public cocos2d::Ref
{
public:
    inline void setImageWidth(int imageWidth) { _imageWidth = imageWidth; }
    inline void setImageHeight(int imageHeight) { _imageHeight = imageHeight; }
    inline void setSource(std::string source) { _source = source; }
    inline int getImageWidth() { return _imageWidth; }
    inline int getImageHeight() { return _imageHeight; }
    inline std::string getSource() { return _source; }
private:
	int _imageWidth;
	int _imageHeight;
	std::string _source;
};

class TileSet : public cocos2d::Ref
{
public:
    static TileSet* create();
    
    inline void setFirstGid(int firstGid) { _firstGid = firstGid; }
    inline void setName(std::string name) { _name = name; }
    inline void setTileWidth(int tileWidth) { _tileWidth = tileWidth; }
    inline void setTileHeight(int tileHeight) { _tileHeight = tileHeight; }
    inline void setTileSet(std::map<int, TileSetTile> tileSet) { _tileSet = tileSet; }
    inline int getFirstGid() { return _firstGid; }
    inline std::string getName() { return _name; }
    inline int getTileWidth() { return _tileWidth; }
    inline int getTileHeight() { return _tileHeight; }
    inline std::map<int, TileSetTile> getTileSet() { return _tileSet; }
private:
	int _firstGid;
	std::string _name;
	int _tileWidth;
	int _tileHeight;
	std::map<int, TileSetTile> _tileSet;
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
	
	std::vector<TileMapLayer*> _tileMapLayers;
	std::vector<TileMapObjectGroup*> _tileMapObjects;

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
