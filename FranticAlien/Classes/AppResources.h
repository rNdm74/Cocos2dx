#ifndef __FranticAlien__APP_RESOURCES_H__
#define __FranticAlien__APP_RESOURCES_H__

#include "cocos2d.h"

// PNG assets
#define BACKGROUND_PNG		"background.png"
#define CHARACTERS_PNG		"characters.png"
#define CONTROLS_PNG		"controls.png"
#define HUD_PNG				"hud.png"
#define ITEMS_PNG			"items.png"
#define PARTICLES_PNG		"particles.png"
#define TILES_PNG			"tiles.png"

// PLIST assets
#define BACKGROUND_PLIST	"background.plist"
#define CHARACTERS_PLIST	"characters.plist"
#define CONTROLS_PLIST		"controls.plist"
#define HUD_PLIST			"hud.plist"
#define ITEMS_PLIST			"items.plist"
#define PARTICLES_PLIST		"particles.plist"
#define TILES_PLIST			"tiles.plist"

using namespace cocos2d;

class AppResources
{
private:
	static AppResources* m_pInstance;

	SpriteFrameCache* cache;
	TextureCache* textureCache;

public:
    static AppResources* getInstance();
    
	bool initLoad();
	bool mainLoad();

private:
    AppResources();
    virtual ~AppResources();
    AppResources(AppResources const&){};
    AppResources& operator=(AppResources const&);

	char* timestamp();
    
    // Sprites
	void loadBackgroundResources(Texture2D* texture);
	void loadCharacterResources(Texture2D* texture);
	void loadControlResources(Texture2D* texture);
	void loadHudResources(Texture2D* texture);
	void loadItemResources(Texture2D* texture);
	void loadParticleResources(Texture2D* texture);
	void loadTileResources(Texture2D* texture);

    
};

#endif // __RESOURCESMANAGER_H__
