#include "World.h"
#include "AppGlobal.h"
#include "Level.h"
#include "GameObject.h"

World* World::create()
{
	// Create an instance of InfiniteParallaxNode
	World* node = new World();

	if (node) {
		// Add it to autorelease pool
		node->autorelease();
	}
	else {
		// Otherwise delete
		delete node;
		node = 0;
	}

	return node;
}

World::World()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 mapOrigin = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (visibleSize.height / 6));

	background = WorldParallaxBackGround::create();
	this->addChild(background);

	for (const auto& child : background->getChildren())
	{
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}

	level = new Level();
	level->loadMap("level1.tmx");
	this->addChild(level->getMap());

	player = GamePlayer::createWithFrameName("alienBeige_stand.png");
	player->setPosition(mapOrigin);
	player->getTexture()->setAntiAliasTexParameters();

	log("pX: %f, pY%f", player->getPositionX(), getPositionY());

	this->addChild(player, 99);
}

World::~World()
{
}

void World::update(float& delta)
{
	this->background->update(delta);
	//this->level->checkCollisions(delta, *player);
	//this->level->update(delta, *player);

	this->player->updateObject(delta, *level);
}

void World::updateLayers()
{
	

	//for (auto& object : this->map->getChildren())
	//{
	//	// is this map child a tile layer?
	//	auto layer = dynamic_cast<TMXLayer*>(object);

	//	if (layer != nullptr)
	//	{
	//		this->updateTiles(layer);
	//	}			
	//}
}

void World::updateTiles(TMXLayer* layer)
{			
	// create all the rectangular fixtures for each tile
	Size layerSize = layer->getLayerSize();

	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{
			// create a fixture if this tile has a sprite
			auto tileSprite = layer->getTileAt(Point(x, y));

			if (tileSprite)
			{
				auto tilePos = convertToWorldSpace(tileSprite->getPosition());
				log("%f, %f", tilePos.x, tilePos.y);
				//if (tileSprite->)

				//tileSprite->removeFromParent();
				
				//this->addChild(tileSprite, 0, Vec2(parallaxRatio, 1), tileSprite->getPosition());
			}				
		}
	}
}

//
//
// 
//
//

WorldParallaxBackGround* WorldParallaxBackGround::create()
{
	// Create an instance of InfiniteParallaxNode
	WorldParallaxBackGround* node = new WorldParallaxBackGround();

	if (node) {
		// Add it to autorelease pool
		node->autorelease();
		node->addBackground();
	}
	else {
		// Otherwise delete
		delete node;
		node = 0;
	}

	return node;
}

WorldParallaxBackGround::WorldParallaxBackGround()
{	
}

WorldParallaxBackGround::~WorldParallaxBackGround()
{
}

void WorldParallaxBackGround::update(float& delta)
{
	float currentX = this->getPositionX();
	currentX += 150 * delta * -1;
	this->setPositionX(currentX);

	this->updateBackground();
}

void WorldParallaxBackGround::updateBackground()
{
	//
	int safeOffset = 0;

	// Get visible size
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 1. For each child of an parallax node
	for (int i = 0; i < _children.size(); i++)
	{
		auto node = _children.at(i);

		// 2. We check whether it is out of the left side of the visible area
		if (convertToWorldSpace(node->getPosition()).x + node->getContentSize().width < safeOffset)
		{
			// 3. Find PointObject that corresponds to current node
			for (int i = 0; i < _parallaxArray->num; i++)
			{
				auto po = (PointObject*)_parallaxArray->arr[i];

				// If yes increase its current offset on the value of visible width
				if (po->getChild() == node)
				{
					//log("offset changed");
					if (node->getTag() == kTagScrollingBackground)
						po->setOffset(po->getOffset() + Point(node->getContentSize().width * 2, 0));
					else if (node->getTag() == kTagScrollingCloud)
					{
						po->setOffset(po->getOffset() + Point(visibleSize.width + node->getContentSize().width, 0));
					}
					else if (node->getTag() == kTagScrollingBush)
					{
						this->removeChild(node, true);
						this->addBushs();
					}
				}
			}
		}
	}
}

void WorldParallaxBackGround::addBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 3; i++)
	{
		auto background = Sprite::create("bg0.png");
		background->setTag(kTagScrollingBackground);
		background->setAnchorPoint(Vec2(0, 0));
		background->setScale(1.2f);
		this->addChild(background, -10, Vec2(0.1, 1), Vec2(i * background->getContentSize().width, 70));

		background = Sprite::createWithSpriteFrameName("groundGrass.png");
		background->setTag(kTagScrollingBackground);
		background->setAnchorPoint(Vec2(0, 0));
		this->addChild(background, -9, Vec2(0.2, 1), Vec2(i * background->getContentSize().width, 70));

		this->addBushs();
		this->addClouds();
	}
}

void WorldParallaxBackGround::addBushs()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::createWithSpriteFrameName("bush.png");
	
	background->setTag(kTagScrollingBush);
	background->setAnchorPoint(Vec2(0, 0));
	background->setScale(RAND(0.7, 2));
	
	this->addChild(background, -8, Vec2(0.4, 1), Vec2(RAND(visibleSize.width, visibleSize.width * 2), 70));
}

void WorldParallaxBackGround::addClouds()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto pos = std::to_string((int)RAND(1, 3));

	auto background = Sprite::createWithSpriteFrameName("cloud" + pos + ".png");

	background->setTag(kTagScrollingCloud);
	background->setAnchorPoint(Vec2(0, 0));
	background->setScale(RAND(0.7, 1));

	float x = RAND(0, visibleSize.width);
	float y = RAND(visibleSize.height / 2, visibleSize.height);

	this->addChild(background, -8, Vec2(RAND(0.1, 0.6), 1), Vec2(x, y));
}
