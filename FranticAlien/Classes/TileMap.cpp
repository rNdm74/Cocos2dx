#include "TileMap.h"

#include "TileMapTile.h"
#include "TileMapObject.h"

#include "AppGlobal.h"
#include "AppResources.h"


USING_NS_CC;

TileMap::TileMap()
{

}

TileMap::~TileMap()
{
}

Node* TileMap::CreateObjectLayer(int level)
{
	Node* objectLayer = Node::create();

	objectLayer->setAnchorPoint(cocos2d::Vec2::ZERO);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::map<int, std::map<int, Vec2>> objectgroup = AppResources::getInstance()->getLevelObjects(level);

	int rows = MAX_ROWS;

	for (std::map<int,std::map<int, Vec2>>::iterator i = objectgroup.begin(); i != objectgroup.end(); ++i)
	{
		//std::map<int, cocos2d::Vec2> object = i->second;


		for (std::map<int, Vec2>::iterator o = i->second.begin(); o != i->second.end(); ++o)
		{
			int gid = o->first;
			Vec2 vec = o->second;

			int x = vec.x;
			int y = (origin.y + visibleSize.height) - ((vec.y) - rows) + (TILE_SIZE);

			y++;
			rows--;

			//char buffer[20];
			//sprintf (buffer, "%d", rows);
			//cocos2d::CCLog("%s", buffer);


			Sprite* object = (Sprite*) TileMapObject::create(gid, x, y);
			object->getTexture()->setAntiAliasTexParameters();
			objectLayer->addChild(object);

			if(gid == 126)
			{
                AppGlobal::getInstance()->StartPosition = Point(x, y);
			}
		}
	}

	return objectLayer;
}

Layer* TileMap::createLayer()
{
    Layer* layer = Layer::create();
    layer->setContentSize(getLayerSize());
    layer->setAnchorPoint(Vec2::ZERO);
    
    Sprite* bg = Sprite::create("bg_grasslands.png");
    bg->setScaleX((layer->getContentSize().width / bg->getContentSize().width) * 1);
    bg->setScaleY((layer->getContentSize().height / bg->getContentSize().height) * 1);
    bg->setAnchorPoint(Vec2::ZERO);
    
    layer->addChild(bg, -1);
    
    return layer;
}

Layer* TileMap::createLayer(int level)
{
    Layer* layer = Layer::create();
    layer->setContentSize(getLayerSize());
    layer->setAnchorPoint(Vec2::ZERO);
    layer->setTag(level);
    
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
 
    for(int row = 0; row < MAX_ROWS; row++)
	{
		for(int col = 0; col <  MAX_COLS; col++)
		{
			int gid = AppResources::getInstance()->getLevelGid(level, row, col);
			
			if(gid != 0)
			{
				float x = layer->getBoundingBox().origin.x + col * TILE_SIZE;
                float y = layer->getBoundingBox().origin.y + layer->getContentSize().height - row * TILE_SIZE ; // Flip to display correctly
                
                TileMapTile* tile = TileMapTile::create(x, y, gid);
                tile->setAnchorPoint(Point::ZERO);
                tile->getTexture()->setAntiAliasTexParameters();
                
				layer->addChild(tile);
			}
		}
	}
    
    return layer;
}
