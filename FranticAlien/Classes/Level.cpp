#include "AppGlobal.h"
#include "Box2D.h"
#include "Constants.h"
#include "ContactListener.h"
#include "GameObject.h"
#include "Level.h"

void Level::loadMap(std::string mapname){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 mapOrigin = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	map = TMXTiledMap::create(mapname);
	map->retain();

	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(mapOrigin);

	for (const auto& child : map->getChildren())
	{
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}
}

Level::Level()
{
	// initialize variables, load the tmx, create the objects, etc...
	createPhysicsWorld();
}

Level::~Level(void)
{
	map->release();
}

void Level::BeginContact(b2Contact* contact)
{
	log("contact begin");
	// call the appropriate LevelObject's beginContact function
	//if (contact && contact->IsTouching())
	//{
	//	// turn fixtures into level objects
	//	LevelObject* A = static_cast<LevelObject*>
	//		(contact->GetFixtureA()->GetBody()->GetUserData());
	//	LevelObject* B = static_cast<LevelObject*>
	//		(contact->GetFixtureB()->GetBody()->GetUserData());

	//	// turn fixtures into player
	//	Player* player = dynamic_cast<Player*>(A);
	//	LevelObject* other = B;
	//	if (player == nullptr)
	//	{
	//		player = dynamic_cast<Player*>(B);
	//		other = A;
	//	}

	//	// call the begin contact
	//	if (A && B)
	//	{
	//		// always prefer to call the player's version of beginContact
	//		if (player && other)
	//			player->beginContact(other, contact);
	//		else
	//			A->beginContact(B, contact);
	//	}
	//}
}

void Level::EndContact(b2Contact* contact)
{
	log("contact end");
	// nothing to do here for the current implementation
}

void Level::createPhysicsWorld()
{
	physicsWorld = new b2World(b2Vec2(0, kGravity));
	
	physicsWorld->SetAllowSleeping(true);
	physicsWorld->SetContinuousPhysics(true);
	physicsWorld->SetContactListener(new ContactListener());
}
void Level::prepareLayers()
{
	for (auto& object : this->map->getChildren())
	{
		// is this map child a tile layer?
		auto layer = static_cast<TMXLayer*>(object);

		if (layer != nullptr)
		{
			this->createFixtures(*layer);
		}			
	}
}
void Level::createFixtures(TMXLayer& layer)
{
	// create all the rectangular fixtures for each tile
	Size layerSize = layer.getLayerSize();

	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{
			// create a fixture if this tile has a sprite
			auto tileSprite = layer.getTileAt(Point(x, y));

			if (tileSprite)
			{
				this->createRectangularFixture(layer, x, y, 1.0f, 1.0f);
			}				
		}
	}
}
void Level::createRectangularFixture(TMXLayer& layer, int x, int y, int width, int height)
{
	// get position & size
	auto p = layer.convertToWorldSpace(layer.getPositionAt(Point(x, y)));
	auto tileSize = this->map->getTileSize();
		
	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set
	(
		(p.x + (tileSize.width / 2.0f)) / kPixelsPerMeter,
		(p.y + (tileSize.height / 2.0f)) / kPixelsPerMeter
	);
	
	b2Body* body = physicsWorld->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox
	(
		(tileSize.width / kPixelsPerMeter) * 0.5f * width,
		(tileSize.width / kPixelsPerMeter) * 0.5f * height
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.2f;
	fixtureDef.filter.categoryBits = kFilterCategoryLevel;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}

void Level::createRectangularFixture(float x, float y, float width, float height, bool isSensor, uint16 categoryBits, uint16 maskBits)
{
	auto worldPos = map->convertToWorldSpace(Vec2(x, y));

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set
	(
		(worldPos.x + width / 2.0f) / kPixelsPerMeter,
		(worldPos.y + height / 2.0f) / kPixelsPerMeter
	);

	b2Body* body = physicsWorld->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox
	(
		(width / kPixelsPerMeter) * 0.5f,
		(height / kPixelsPerMeter) * 0.5f 
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.02f;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.isSensor = isSensor;
	body->CreateFixture(&fixtureDef);
}

void Level::createGhostFixture(float x, float y, float width, float height, bool isSensor, uint16 categoryBits, uint16 maskBits)
{
	auto worldPos = map->convertToWorldSpace(Vec2(x, y));

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(0, 0);
	
	b2Body* body = physicsWorld->CreateBody(&bodyDef);
	
	b2EdgeShape edgeShape;

	b2Vec2 v1 = b2Vec2
	(
		worldPos.x / kPixelsPerMeter,
		(worldPos.y + height) / kPixelsPerMeter
	);
	
	b2Vec2 v2 = b2Vec2
	(
		(worldPos.x + width) / kPixelsPerMeter,
		(worldPos.y + height) / kPixelsPerMeter
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &edgeShape;
	edgeShape.Set(v1, v2);
	edgeShape.m_vertex0.Set(v1.x - 1, v1.y);
	edgeShape.m_vertex3.Set(v2.x + 1, v2.y);
	edgeShape.m_hasVertex0 = true;
	edgeShape.m_hasVertex3 = true;

	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.02f;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.isSensor = isSensor;
	body->CreateFixture(&fixtureDef);
}

void Level::createPolyLineFixture(std::vector<b2Vec2> vectors, int32 count, bool isSensor, uint16 categoryBits, uint16 maskBits)
{
	//auto worldPos = map->convertToWorldSpace(Vec2(x, y));

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(0, 0);

	b2Body* body = physicsWorld->CreateBody(&bodyDef);

	b2PolygonShape polyShape;
	
	
	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	polyShape.m_count = count;

	for (int i = 0; i < count; i++)
	{
		polyShape.m_vertices[i].Set(vectors.at(i).x, vectors.at(i).y);
	}

	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.02f;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.isSensor = isSensor;
	body->CreateFixture(&fixtureDef);
}

void Level::addObjects()
{
	// loop over the object groups in this tmx file
	auto objectGroups = map->getObjectGroups();
	for (auto& objectGroup : objectGroups)
	{
		auto objects = objectGroup->getObjects();
		for (auto& object : objects)
		{
			auto test = object.getType();

			auto properties = object.asValueMap();
			auto type = properties.at("type");

			if (!type.isNull())
			{
				this->addObject(type.asString().c_str(), properties);
				this->objectCount++;
			}
		}
	}
}

GameObject* Level::addObject(std::string className, ValueMap& properties)
{	
	auto x = properties["x"].asFloat();
	auto y = properties["y"].asFloat();
	auto width = properties["width"].asFloat();
	auto height = properties["height"].asFloat();

	if (className == "Ghost")
		this->createGhostFixture(x, y, width, height, false, kFilterCatagory::BOUNDARY, kFilterCatagory::PLAYER | kFilterCatagory::ENEMY);
	else if (className == "Ladder")
		this->createRectangularFixture(x, y, width, height, false, kFilterCatagory::LADDER, kFilterCatagory::PLAYER | kFilterCatagory::ENEMY);
	else if (className == "Bounds")	
		this->createRectangularFixture(x, y, width, height, false, kFilterCatagory::BOUNDARY, kFilterCatagory::PLAYER | kFilterCatagory::ENEMY);
		

	// create the object
	GameObject* o = nullptr;

	//if (className == "GamePlayer")
	//	o = GamePlayer::createWithFrameName("alienBeige_stand.png");

	///*else if (className == "Monster")
	//	o = new Monster;
	//else if (className == "MagicChest")
	//	o = new MagicChest;*/

	//// process the new object
	//if (o != nullptr)
	//{
	//	o->setProperties(properties);
	//	o->addBodyToWorld(*physicsWorld);
	//	o->addFixturesToBody();
	//	this->addChild(o);
	//}

	return o;
}

void Level::update(float& delta)
{
	physicsWorld->Step(delta, 1, 1);
}