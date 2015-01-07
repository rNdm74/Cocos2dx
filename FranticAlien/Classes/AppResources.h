#ifndef __FranticAlien__APP_RESOURCES_H__
#define __FranticAlien__APP_RESOURCES_H__

#include "cocos2d.h"

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
