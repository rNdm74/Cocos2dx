#include "TileMap.h"

#include "TileMapTile.h"
#include "TileMapObject.h"

#include "AppGlobal.h"
#include "AppResources.h"

USING_NS_CC;

TileSet* TileSet::create()
{
	// Create an instance of InfiniteParallaxNode
	TileSet* node = new TileSet();

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

TileMap* TileMap::create(std::string filename)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create an instance of InfiniteParallaxNode
	TileMap* node = new TileMap();

	if (node && node->initWithTMXFile(filename)) {


		// Add it to autorelease pool
		node->autorelease();
		node->setPosition(origin);
		//node->setAnchorPoint(Vec2::ZERO);
		node->addBackground();
		node->addLayers();
	}
	else {
		// Otherwise delete
		delete node;
		node = 0;
	}

	return node;
}

void TileMap::tilesetswitch(tinyxml2::XMLElement* node)
{
	//	EXAMPLE
	
	// <tileset firstgid="1" name="Tiles" tilewidth="70" tileheight="146">
	//		<tile id="0">
	//			<image width="70" height="70" source="box.png"/>
	//		</tile>
	// </tileset>

	// Create tileset object
	tileset = TileSet::create();

	// Attributes
	node->QueryIntAttribute("firstgid", &tileset->_firstgid);
	tileset->_name = node->Attribute("name");
	node->QueryIntAttribute("tilewidth", &tileset->_tilewidth);
	node->QueryIntAttribute("tileheight", &tileset->_tileheight);

	// Get the tile node
	auto tileNode = node->FirstChildElement();

	// Iterate through all tileset tiles
	for (auto t = tileNode; t != NULL; t = t->NextSiblingElement())
	{
		// id of tile node
		int key;
		t->QueryIntAttribute("id", &key);

		// Get the image node
		auto imageNode = t->FirstChildElement();

		// Attributes
		imageNode->QueryIntAttribute("width", &tileset->_tiles[key]._imagewidth);
		imageNode->QueryIntAttribute("height", &tileset->_tiles[key]._imageheight);
		tileset->_tiles[key]._source = imageNode->Attribute("source");
	}
}

void TileMap::layerswitch(tinyxml2::XMLElement* node)
{
	//	EXAMPLE

	// <layer name="0" width="17" height="11">
	//		<data>
	//			<tile gid="0"/>
	//			<tile gid="0"/>
	//		</data>
	// </layer>

	// 
	
	// Create the tilemap layer
	auto layer = new TileMapLayer();
	
	// Attributes
	layer->_name = node->Attribute("name");
	node->QueryIntAttribute("width", &layer->_width);
	node->QueryIntAttribute("height", &layer->_height);
	
	// Move to data node
	auto data = node->FirstChildElement();

	// Move to tile node
	auto tileNode = data->FirstChildElement();
	
	// Iterate through all tiles
	for (auto t = tileNode; t != NULL; t = t->NextSiblingElement())
	{
		int gid;
		t->QueryIntAttribute("gid", &gid);
		layer->_layerInfo.push_back(gid);
	}

	// Add to the total layer list
	layers.push_back(layer);
}

void TileMap::objectgroupswitch(tinyxml2::XMLElement* node)
{
	//	EXAMPLE

	// <objectgroup name="0">
	//		<object gid="12" x="280" y="700"/>
	// </objectgroup>

	// Create the tilemap layer
	auto objectgroup = new TileMapObjectGroup();


	// Attributes
	objectgroup->_name = node->Attribute("name");

	// Move to object node
	auto objectNode = node->FirstChildElement();
	
	// Iterate through all tiles
	for (auto t = objectNode; t != NULL; t = t->NextSiblingElement())
	{
		TileMapObject object;

		int gid, x, y;
		t->QueryIntAttribute("gid", &object._gid);
		t->QueryIntAttribute("x", &object._x);
		t->QueryIntAttribute("y", &object._y);
		
		objectgroup->_objectInfo.push_back(object);
	}

	// Add to the total layer list
	objects.push_back(objectgroup);
}

bool TileMap::initWithTMXFile(std::string filename)
{
	CCASSERT(filename.size() > 0, "Invalid filename for tilemap");

	auto document = AppResources::getInstance()->loadXMLDocument(filename);
	
	// <map version="1.0" orientation="orthogonal" renderorder="left-down" width="17" height="11" tilewidth="70" tileheight="70">
	auto map = document->RootElement();
	
	// Attributes
	_version = map->Attribute("version");
	_orientation = map->Attribute("orientation");
	_renderorder = map->Attribute("renderorder");

	map->QueryIntAttribute("width", &_width);
	map->QueryIntAttribute("height", &_height);
	map->QueryIntAttribute("tilewidth", &_tilewidth);
	map->QueryIntAttribute("tileheight", &_tileheight);

	//
	std::map < std::string, int > nodeMap;
	nodeMap["tileset"] = 0;
	nodeMap["layer"] = 1;
	nodeMap["objectgroup"] = 2;

	//
	for (auto node = map->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
	{	
		switch (nodeMap[node->Name()])
		{
			case 0:
				log("tileset switch");
				tilesetswitch(node);
				break;
			case 1:
				log("layer switch");
				layerswitch(node);
				break;
			case 2:
				log("objectgroup switch");
				objectgroupswitch(node);
				break;
		}
	}
	
	return true;
}

void TileMap::updatePosition()
{
	//
	int safeOffset = -10;

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
					if (node->getTag() == 74)
					{
						po->setOffset(po->getOffset() + Point(node->getContentSize().width * 2, 0));
					}
					else
					{
						po->setOffset(po->getOffset() + Point(visibleSize.width + node->getContentSize().width * 2, 0));
					}					
				}
			}
		}
	}	
}

TileMap::TileMap()
{

}

TileMap::~TileMap()
{
}

void TileMap::addBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 3; i++)
	{
		auto background = Sprite::create("background.png");
		background->setTag(74);
		background->setAnchorPoint(Vec2(0, 0));
		this->addChild(background, -10, Vec2(0.2, 1), Vec2( i * background->getContentSize().width, visibleSize.height - (4 * 70)));

		background = Sprite::create("groundGrass.png");
		background->setTag(74);
		background->setAnchorPoint(Vec2(0, 0));
		this->addChild(background, -9, Vec2(0.3, 1), Vec2(i * background->getContentSize().width, visibleSize.height - (4 * 70)));

		background = Sprite::create("cloud" + std::to_string(i + 1) + ".png");
		background->setAnchorPoint(Vec2(0, 0));
		background->setScale(RAND(0.7, 1));
		this->addChild(background, -8, Vec2(RAND(0.1, 0.6), 1), Vec2(i * background->getContentSize().width + RAND(0, visibleSize.width), (visibleSize.height - 100) - RAND(0, background->getContentSize().height)));

		background = Sprite::create("bush.png");
		background->setAnchorPoint(Vec2(0, 0));
		this->addChild(background, -8, Vec2(0.4, 1), Vec2(i * background->getContentSize().width + RAND(0, visibleSize.width), visibleSize.height - (4 * 70)));
	}
}

void TileMap::addLayers()
{	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
		
	for (auto l : layers)
	{
		for(int row = 0; row < l->_height; row++)
		{
			for(int col = 0; col <  l->_width; col++)
			{
				int index = row * l->_width + col;

				int gid = l->_layerInfo[index];
				
				if (gid != 0)
				{
					float x = (origin.x + col * 69);
					float y = ((origin.y + visibleSize.height) - row * 69);
					float z = std::atoi(l->_name.c_str());

					TileMapTile* tile = TileMapTile::create(x, y, gid);
					
					float offsetX = tile->getContentSize().width / 2;
					float offsetY = tile->getContentSize().height / 2;

					this->addChild(tile, z, Vec2(z / 3 + 0.1f , 1), Vec2(x + offsetX, y - offsetY));
				}		
			}
		}
	}
}