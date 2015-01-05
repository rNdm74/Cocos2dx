#ifndef __FranticAlien__WORLD_H__
#define __FranticAlien__WORLD_H__

#include "cocos2d.h"

class AppGlobal;
class Level;
class GamePlayer;

#define kTagScrollingBackground 0
#define kTagScrollingCloud 1
#define kTagScrollingBush 2

using namespace cocos2d;

class WorldParallaxBackGround : public cocos2d::ParallaxNode
{
	class PointObject : public cocos2d::Ref
	{
	public:
		void setRation(cocos2d::Point ratio) { _ratio = ratio; }
		void setOffset(cocos2d::Point offset) { _offset = offset; }
		void setChild(cocos2d::Node *var) { _child = var; }
		cocos2d::Point getOffset() const { return _offset; }
		cocos2d::Node* getChild() const { return _child; }
	private:
		cocos2d::Point _ratio;
		cocos2d::Point _offset;
		cocos2d::Node* _child;
	};

public:
	// "creator" methods first	
	static WorldParallaxBackGround* create();

	// If applicable, then Constructors and the Destructor
	WorldParallaxBackGround();
	virtual ~WorldParallaxBackGround();

	void update(float& delta);
	void updateBackground();

	void addBackground();
	void addBushs();
	void addClouds();

};

class World : public Node
{
public:
	// "creator" methods first	
	static World* create();

	// If applicable, then Constructors and the Destructor
	World();
	virtual ~World();

	void update(float& delta);
	void updateLayers();

	void updateTiles(TMXLayer* layer);
	
private:
	GamePlayer* player;
	Level* level;
	WorldParallaxBackGround* background;
};





#endif /* defined(__FranticAlien__WORLD_H__) */
