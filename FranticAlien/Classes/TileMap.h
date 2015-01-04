#ifndef __FranticAlien__TILEMAP_H__
#define __FranticAlien__TILEMAP_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
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
    void setName(std::string name) { _name = name; }
    void setObjectInfo(std::vector<TileMapObject> objectInfo) { _objectInfo = objectInfo; }
    std::string getName(){ return _name; }
    std::vector<TileMapObject> getObjectInfo() { return _objectInfo; }
private:
	std::string _name;	
	std::vector<TileMapObject> _objectInfo;
};

class TileMapLayer : public cocos2d::Ref
{
public:
    void setName(std::string name) { _name = name; }
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }
    void setLayerInfo(std::vector<int> layerInfo) { _layerInfo = layerInfo; }
    std::string getName() { return _name; }
    int getWidth() { return _width; }
    int getHeight() { return _height; }
    std::vector<int> getLayerInfo() { return _layerInfo; }
    int getLayerInfoAt(int index) { return _layerInfo[index]; }
private:
	std::string _name;
	int _width;
	int _height;
	std::vector<int> _layerInfo;
};

class TileSetTile : public cocos2d::Ref
{
public:
    void setImageWidth(int imageWidth) { _imageWidth = imageWidth; }
    void setImageHeight(int imageHeight) { _imageHeight = imageHeight; }
    void setSource(std::string source) { _source = source; }
    int getImageWidth() { return _imageWidth; }
    int getImageHeight() { return _imageHeight; }
    std::string getSource() { return _source; }
private:
	int _imageWidth;
	int _imageHeight;
	std::string _source;
};

class TileSet : public cocos2d::Ref
{
public:
    static TileSet* create();
    
    void setFirstGid(int firstGid) { _firstGid = firstGid; }
    void setName(std::string name) { _name = name; }
    void setTileWidth(int tileWidth) { _tileWidth = tileWidth; }
    void setTileHeight(int tileHeight) { _tileHeight = tileHeight; }
    void setTileSet(std::map<int, TileSetTile> tileSet) { _tileSet = tileSet; }
    int getFirstGid() { return _firstGid; }
    std::string getName() { return _name; }
    int getTileWidth() { return _tileWidth; }
    int getTileHeight() { return _tileHeight; }
    std::map<int, TileSetTile> getTileSet() { return _tileSet; }
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

	std::vector<TileSet*> _tileSets;
	std::vector<TileMapLayer*> _tileMapLayers;
	std::vector<TileMapObjectGroup*> _tileMapObjects;

public:
	// "creator" methods first	
	static TileMap* create(std::string filename);

	// If applicable, then Constructors and the Destructor
	TileMap();
	virtual ~TileMap();

	// Then the init methods
	bool initWithTMXFile(std::string filename);

	// Then methods of the instance
	void tilesetswitch(tinyxml2::XMLElement* node);
	void layerswitch(tinyxml2::XMLElement* node);
	void objectgroupswitch(tinyxml2::XMLElement* node);

	void updatePosition();
	
	

	static cocos2d::Sprite* createLayer(std::string fileName);
    
    
    // Then the overrides
    static cocos2d::Size getLayerSize(){ return cocos2d::Size(MAX_COLS * TILE_SIZE, MAX_ROWS * TILE_SIZE); };
    float getLayerWidth() { return MAX_COLS * TILE_SIZE; };
    float getLayerHeight() { return MAX_ROWS * TILE_SIZE; };

private:
	void addBackground();
	void addLayers();
};

#endif // __TILEMAP_H__
