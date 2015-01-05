#ifndef __FranticAlien__LEVEL_H__
#define __FranticAlien__LEVEL_H__

#include "cocos2d.h"

class GameObject;

using namespace cocos2d;

class Level : public Node
{
public:
	TMXTiledMap *map;

	void loadMap(const char* name);
	TMXTiledMap * getMap();

	Level();
	virtual ~Level(void);

	void setupResources();
	void addWorldObjects(TMXLayer& layer);

	void update(float& delta, GameObject& player);

	void checkCollisions(float& delta, GameObject& player);
	void checkTiles(float& delta, TMXLayer& layer, GameObject& player);

private:
	// The number of objects in the game world
	int worldObjectCount;

	// The geometry of all the landscape objects (platforms and walls)
	Vector<Node*> worldObjects;

	// Pre-calculated bounding boxes for all the landscape objects
	std::vector<Rect> worldObjectBoundingBoxes;
		
	// The maximum number of iterations for the contact solver to run per frame
	static const int iterations = 3;

	// Statistics on the contact solver per frame
	typedef struct {
		int boundConstraints;
		int penetrationCorrections;
		int specSteps;
		int specDiscards;
		int contacts;
	} CollisionData;

	CollisionData CollisionStats[iterations];

	// A list of objects this frame for which the player is currently within the bounding boxes of
	// (these are the only objects that will be tested for collision)
	std::set<int> boundObjects;

	// True if the bounding boxes should be rendered (for debugging)
	bool showBoundingBoxes;
};

#endif /* defined(__FranticAlien__LEVEL_H__) */
