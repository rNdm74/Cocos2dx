#include "AppResources.h"

USING_NS_CC;

AppResources* AppResources::m_pInstance = NULL;

AppResources* AppResources::getInstance()
{
	return m_pInstance ? m_pInstance : m_pInstance = new AppResources();
}

AppResources::AppResources()
{
    cache = SpriteFrameCache::getInstance();
}

AppResources::~AppResources()
{
}

bool AppResources::Load()
{
    //loadLevels();
    loadPlayerResources();
    //loadEnemyResources();
    //loadObjectResources();
    loadTileResources();
    
    return true;
}

void AppResources::loadLevels()
{
	auto document = loadXMLDocument(XML_TILED_MAP_EDITOR);
	
	tinyxml2::XMLElement* element = loadXMLDocument(XML_TILED_MAP_EDITOR)->FirstChildElement()->FirstChildElement();

	for(tinyxml2::XMLElement* e = element; e != NULL; e = e->NextSiblingElement())
	{
		int key, width, height;

		std::string eName = e->Name();

		e->QueryIntAttribute("name", &key);
		e->QueryIntAttribute("width", &width);
		e->QueryIntAttribute("height", &height);

		if(eName.compare("layer") == 0)
		{
			//CCLog("%s", "layer");

			level_map[key] = new int[width*height];

			int index = 0;

			for(tinyxml2::XMLElement* tile = e->FirstChildElement()->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement())
				tile->QueryIntAttribute("gid", &level_map[key][index++]);
		}
		else if(eName.compare("objectgroup") == 0)
		{
			int index = 0;

			for(tinyxml2::XMLElement* object = e->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
			{
				int gid, x, y;
				object->QueryIntAttribute("gid", &gid);
				object->QueryIntAttribute("x", &x);
				object->QueryIntAttribute("y", &y);

				object_map[key][index++][gid] = Vec2(x, y);
			}
		}
	}
}

void AppResources::loadPlayerResources()
{
    
    //cache->addSpriteFramesWithFile("alienBeige.plist");
    
    auto document = loadXMLDocument("Spritesheets/aliens.xml");
    
    auto textureAtlas = document->FirstChildElement();
    
    auto subTexture = textureAtlas->FirstChildElement();
    
    for(auto sub = subTexture; sub != NULL; sub = sub->NextSiblingElement())
    {
        int x, y, width, height;
        sub->QueryIntAttribute("x", &x);
        sub->QueryIntAttribute("y", &y);
        sub->QueryIntAttribute("width", &width);
        sub->QueryIntAttribute("height", &height);
        
        //framename_map[key] = sub->Attribute("name");
        
        cache->addSpriteFrame(SpriteFrame::create("Spritesheets/aliens.png", Rect(x, y + 0.2, width, height - 0.8)), sub->Attribute("name"));
        
    }
    
	log("%s", "Loaded Player Resources");
}
void AppResources::loadEnemyResources()
{
	log("%s", "Loaded Enemy Resources");
}
void AppResources::loadObjectResources()
{
	log("%s", "Loaded Object Resources");
}

void AppResources::loadTileResources()
{
	auto element = loadXMLDocument(XML_TILES_SPRITESHEET)->FirstChildElement()->FirstChildElement();

	int key = 0;

	for(auto e = element; e != NULL; e = e->NextSiblingElement())
	{
		//log("%s", e->Attribute("name"));

		int x, y, width, height;
	 	e->QueryIntAttribute("x", &x);
	   	e->QueryIntAttribute("y", &y);
	   	e->QueryIntAttribute("width", &width);
	   	e->QueryIntAttribute("height", &height);

	   	framename_map[key] = e->Attribute("name");

	   	cache->addSpriteFrame(SpriteFrame::create(IMG_TILES_SPRITESHEET, Rect(x, y, width, height)), framename_map[key]);

	   	key++;
	}

	log("%s", "Loaded Tile Resources");
}

tinyxml2::XMLDocument* AppResources::loadXMLDocument(std::string filename)
{
	// If invalid string throw error
	CCASSERT(filename.size() > 0, "Invalid filename for xml document");
	
	// Load string from file
	auto fileContents = FileUtils::getInstance()->getStringFromFile(filename);

	// Create new XMLDocument for parsing
	auto doc = new tinyxml2::XMLDocument(true, tinyxml2::Whitespace::COLLAPSE_WHITESPACE);

	// Allow document to parse string information
	doc->Parse(fileContents.c_str(), fileContents.size());

	// Return the built XMLDocument
	return doc;
}
