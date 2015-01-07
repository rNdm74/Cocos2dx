#include "AppResources.h"
#include "Constants.h"


AppResources* AppResources::m_pInstance = NULL;

AppResources* AppResources::getInstance()
{
	return m_pInstance ? m_pInstance : m_pInstance = new AppResources();
}

AppResources::AppResources()
{
    cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(HUD_PLIST); 
	
	textureCache = Director::getInstance()->getTextureCache();
}

AppResources::~AppResources()
{
}

bool AppResources::initLoad()
{	
	//log(" Started loading assets: %s", timestamp());
	textureCache->addImageAsync(BACKGROUND_PNG, CC_CALLBACK_1(AppResources::loadBackgroundResources, this));
	
	textureCache->addImageAsync(CHARACTERS_PNG, CC_CALLBACK_1(AppResources::loadCharacterResources, this));
			
	textureCache->addImageAsync(HUD_PNG, CC_CALLBACK_1(AppResources::loadHudResources, this));
			    
    return true;
}

bool AppResources::mainLoad()
{
	//textureCache->addImageAsync(CONTROLS_PNG, CC_CALLBACK_1(AppResources::loadControlResources, this));

	textureCache->addImageAsync(ITEMS_PNG, CC_CALLBACK_1(AppResources::loadItemResources, this));

	textureCache->addImageAsync(PARTICLES_PNG, CC_CALLBACK_1(AppResources::loadParticleResources, this));

	//textureCache->addImageAsync(TILES_PNG, CC_CALLBACK_1(AppResources::loadTileResources, this));

	return true;
}

void AppResources::loadBackgroundResources(Texture2D* texture)
{	
	//log("Loaded background texture: %s", timestamp());

	cache->addSpriteFramesWithFile(BACKGROUND_PLIST, texture);

	//log("Loaded background plist: %s", timestamp());
}

void AppResources::loadCharacterResources(Texture2D* texture)
{
	//log("Loaded character texture: %s", timestamp());

	cache->addSpriteFramesWithFile(CHARACTERS_PLIST, texture);

	//log("Loaded character plist: %s", timestamp());
}

void AppResources::loadControlResources(Texture2D* texture)
{
	//log("Loaded control texture: %s", timestamp());

	cache->addSpriteFramesWithFile(CONTROLS_PLIST, texture);

	//log("Loaded control plist: %s", timestamp());
}

void AppResources::loadHudResources(Texture2D* texture)
{
	//log("Loaded hud texture: %s", timestamp());

	cache->addSpriteFramesWithFile(HUD_PLIST, texture);

	//log("Loaded hud plist: %s", timestamp());

	
}

void AppResources::loadItemResources(Texture2D* texture)
{
	//log("Loaded item texture: %s", timestamp());

	cache->addSpriteFramesWithFile(ITEMS_PLIST, texture);

	//log("Loaded item plist: %s", timestamp());
}

void AppResources::loadParticleResources(Texture2D* texture)
{
	//log("Loaded particle texture: %s", timestamp());

	cache->addSpriteFramesWithFile(PARTICLES_PLIST, texture);

	//log("Loaded particle plist: %s", timestamp());
}

void AppResources::loadTileResources(Texture2D* texture)
{
	//log("Loaded tile texture: %s", timestamp());

	cache->addSpriteFramesWithFile(TILES_PLIST, texture);

	//log("Loaded tile plist: %s", timestamp());
}