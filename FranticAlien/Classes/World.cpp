#include "World.h"
#include "Constants.h"
#include "AppGlobal.h"
#include "Level.h"
#include "GameObject.h"
#include "B2DebugDrawLayer.h"

#pragma region WorldParallaxBackGround
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
#pragma endregion WorldParallaxBackGround


#pragma region World
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
	Vec2 mapOrigin = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);

	background = WorldParallaxBackGround::create();
	this->addChild(background);

	for (const auto& child : background->getChildren())
	{
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}

	level = new Level();
	level->loadMap(kLevelTMX);
	//level->prepareLayers();
	level->addObjects();
	this->addChild(level->getMap());

	player = GamePlayer::createWithFrameName(kPlayerFileName);
	player->setPosition(mapOrigin);
	player->getTexture()->setAntiAliasTexParameters();
	player->addBodyToWorld(*level->getPhysicsWorld());
	player->addFixturesToBody();
	this->addChild(player, 99);

	//debugDraw = B2DebugDrawLayer::create(level->getPhysicsWorld(), kPixelsPerMeter, 0);
	//this->addChild(debugDraw);
}

World::~World()
{
}



void World::update(float& delta)
{
	background->update(delta);
	level->update(delta);
	player->update(delta, *level->getPhysicsWorld());
}

#pragma endregion World