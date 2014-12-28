#include "TileMapObject.h"
#include "AppResources.h"

USING_NS_CC;

TileMapObject* TileMapObject::create(int gid, float x, float y)
{
	std::string spriteFrameName = AppResources::getInstance()->getFrameName(gid);

	TileMapObject* sprite = new TileMapObject();

	if(sprite && sprite->initWithSpriteFrameName(spriteFrameName))
	{
		sprite->autorelease();

		sprite->setPosition(x, y);
		sprite->setAnchorPoint(cocos2d::Point::ZERO);
		//sprite->getTexture()->setAliasTexParameters();

		return sprite;
	}

	CC_SAFE_DELETE(sprite);

	return NULL;
}
