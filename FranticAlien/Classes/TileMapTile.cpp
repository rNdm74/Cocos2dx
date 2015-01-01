#include "TileMapTile.h"
#include "AppResources.h"
#include "AppGlobal.h"

USING_NS_CC;

TileMapTile::TileMapTile()
{
   
}

TileMapTile* TileMapTile::create(float x, float y, int gid)
{    
	std::string spriteFrameName = AppResources::getInstance()->getFrameName(gid);
   
    if(gid == 126)
    {
        AppGlobal::getInstance()->StartPosition = Point(x, y);
    }
    
	TileMapTile* sprite = new TileMapTile();
    
	if(sprite && sprite->initWithSpriteFrameName(spriteFrameName))
	{
		sprite->autorelease();
        sprite->setTag(gid); 
		
		auto body = PhysicsBody::createBox(sprite->getBoundingBox().size, PhysicsMaterial(0, 0, 0));

		body->setDynamic(false);
		body->setRotationEnable(false);
		body->setCollisionBitmask(1);
		body->setContactTestBitmask(true);
		body->setGravityEnable(false);

		if (gid == 83)
		{
			sprite->setPhysicsBody(body);
		}

		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}