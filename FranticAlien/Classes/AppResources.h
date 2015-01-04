#ifndef __FranticAlien__APP_RESOURCES_H__
#define __FranticAlien__APP_RESOURCES_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"


#define XML_TILES_SPRITESHEET "tiles_spritesheet.xml"
#define XML_TILED_MAP_EDITOR "tiles_spritsheet.tmx"
#define IMG_TILES_SPRITESHEET "tiles_spritesheet.png"

#define MAX_COLS 17

class AppResources
{
private:
	static AppResources* m_pInstance;

	cocos2d::SpriteFrameCache* cache;

	std::map<int, std::string> framename_map;
	std::map<int, int*> level_map;

		   //Level       //Index       //Gid         //x,y
	std::map<int, std::map<int ,std::map<int, cocos2d::Vec2>>> object_map;

public:
    static AppResources* getInstance();
    
    bool Load();

	// XML
	tinyxml2::XMLDocument* loadXMLDocument(std::string filename);

    std::string getFrameName(int gid) { return framename_map[gid - 1]; };
    int getLevelGid(int level, int row, int col){ return level_map[level][row * MAX_COLS + col]; };
    std::map<int, std::map<int, cocos2d::Vec2>> getLevelObjects(int level){ return object_map[level]; };

private:
    AppResources();
    virtual ~AppResources();
    AppResources(AppResources const&){};
    AppResources& operator=(AppResources const&);

    void loadLevels();
    
    // Sprites
    void loadPlayerResources();
    void loadEnemyResources();
    void loadObjectResources();
    void loadTileResources();

    
};

#endif // __RESOURCESMANAGER_H__
