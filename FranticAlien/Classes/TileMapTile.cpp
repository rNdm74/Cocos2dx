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
        sprite->setAnchorPoint(Vec2::ZERO);
        
        // ground
		if (gid == 83)
		{
//            auto body = PhysicsBody::createBox(sprite->getBoundingBox().size, PhysicsMaterial(0, 0, 0));
//            
//            body->setDynamic(false);
//            body->setRotationEnable(false);
//            body->setCollisionBitmask(1);
//            body->setContactTestBitmask(true);
//            body->setGravityEnable(false);
//            
//			sprite->setPhysicsBody(body);
		}
        else if(gid == 76) // angle
        {
            //<object x="350" y="280">
            //<polygon points="0,0 70,-70 70,0"/>
            //</object>
            
            //auto size = sprite->getContentSize();
            
//            auto box = sprite->getBoundingBox();
//            
//            Vec2 points[] =
//            {
//                Vec2(box.origin.x, box.origin.y),
//                Vec2(box.origin.x + box.size.width, box.origin.y + box.size.height),
//                Vec2(box.origin.x + box.size.width, box.origin.y)
//                
//            };
//            
//            auto body = PhysicsBody::createPolygon(points, 3, PhysicsMaterial(0, 0, 0));
//            
//            body->setDynamic(false);
//            body->setRotationEnable(false);
//            body->setCollisionBitmask(1);
//            body->setContactTestBitmask(true);
//            body->setGravityEnable(false);
//            
//            sprite->setPhysicsBody(body);
        }

		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}